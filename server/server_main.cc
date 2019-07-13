#include "precompiled.hh"

#include <thread>

#include "argonx/cmclient/cmclient.hh"
#include "steam/interfaces/helpers.hh"

#include "platform.hh"

void *noUserInterfaceStorage[(u32)Steam::InterfaceTarget::max];
void  CreateNoUserInterfaceStorage() {
    void *r[] = {
        nullptr,                                               // user
        nullptr,                                               // appList
        nullptr,                                               // apps
        nullptr,                                               // client
        Steam::CreateInterface("ClientEngineServer", nullptr), // engine
        nullptr,                                               // controller
        nullptr,                                               // friends
        nullptr,                                               // gameserver
        nullptr,                                               // remotestorage
        nullptr,                                               // ugc
        nullptr,                                               // userstats
        Steam::CreateInterface("ClientUtilsServer", nullptr),  // utils

        nullptr, // argon
    };

    memcpy(noUserInterfaceStorage, r, sizeof(r));
}

static std::unordered_map<Pipe::Target, std::chrono::time_point<std::chrono::system_clock>> heartbeats;

void CreateServerPipe() {
    Steam::SetServerPipe(new Pipe(true, "tcp://127.0.0.1:33901", 33901));
    Steam::ServerPipe()->processMessage = [](Pipe::Target target, u8 *data, u32 size) {
        printf("[serverpipe] size:%d\n", size);

        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        i64 jobId = b.Read<i64>();

        if (jobId < 0) {
            printf("Recieved non-call job %lld\n", jobId);
            // Non-call job
            auto header = b.Read<Steam::RpcNonCallHeader>();

            switch (header.t) {
            case Steam::RpcType::heartbeat: {
                printf("Recieved Heartbeat from %d\n", target);
                heartbeats[target] = std::chrono::system_clock::now();

                // Send it straight back
                Steam::ServerPipe()->SendMessage(target, data, size);
            } break;
            }
        } else {
            Steam::RpcCallHeader header;
            b.ReadInto(header);

            printf("userHandle:%d\n", header.userHandle);

            void *instance = nullptr;

            if (header.userHandle == ~0) {
                // TODO: function for this
                // TODO: also no user *could* just be a normal user (-1)
                instance = noUserInterfaceStorage[(u32)header.targetInterface];
            } else {
                instance = Steam::GetUserInterface((Steam::UserHandle)header.userHandle, header.targetInterface);
            }

            // If the interface was not gettable as a no-user then this will error
            AssertAlways(instance != nullptr, "Instance was 0 when userHandle was %d", header.userHandle);

            using DispatchFromBufferFn = Buffer (*)(void *instance, u32 functionIndex, Buffer &);

            // TODO: find a better way to make this magic happen
            // At the moment we HOPE (and pray) that the dispatches are in the same order on the client
            // and the server but that might not be the case (different os / compiler / whatever)

            auto dispatch = Steam::RpcDispatches()[header.dispatchIndex];
            auto fn       = (DispatchFromBufferFn)dispatch.first;

            // Set the base of the buffer to where the dispatcher wants it
            b.SetBaseAtCurPos();

            // Call the dispatch function for this function
            // which will deserialise the args call the function and then serialise the results
            b = fn(instance, header.functionIndex, b);

            printf("Target:%s index:%d\n", Steam::InterfaceName(header.targetInterface), header.functionIndex);

            // Paste the jobid back onto the front of the buffer and send it back
            b.SetPos(0);
            b.Write(jobId);
            b.SetPos(0);

            Steam::ServerPipe()->SendMessage(target, b.Read(0), b.Size());
        }
    };
}

int main(const int argCount, const char **argStrings) {
    CreateNoUserInterfaceStorage();

    CreateServerPipe();
    std::thread serverThread{
        []() {
            std::vector<Pipe::Target> keysToErase;

            while (true) {
                keysToErase.clear();

                Steam::ServerPipe()->ProcessMessages();

                using namespace std::chrono_literals;
                std::this_thread::sleep_for(1ms);

                auto now = std::chrono::system_clock::now();

                for (auto &[k, v] : heartbeats) {
                    if ((now - v) > 2min) {
                        printf("Dropping client %d\n", k);
                        Steam::ServerPipe()->ClientDisconnected(k);
                        keysToErase.push_back(k);
                    }
                }

                for (auto k : keysToErase) {
                    heartbeats.erase(k);
                }
            }
        }};

#if 0
    printf("%d trampolines allocated (%d bytes)...\n",
           Steam::InterfaceHelpers::TAllocator()->NumAllocated(),
           Steam::InterfaceHelpers::TAllocator()->BytesAllocated());

    {
        u32 counter = 0;
        for (auto &p : Steam::RpcDispatches()) {
            printf("%d: %s\n", counter++, p.second);
        }
    }
    {
        extern Steam::InterfaceHelpers::InterfaceReg *GetInterfaceList();

        auto head  = GetInterfaceList();
        auto total = 0;

        for (auto cur = head; cur != nullptr; cur = cur->next) {
            total += 1;
            printf("[I%s] %s\n", cur->requiresUser ? "u" : " ", cur->name);
        }

        printf("[I] %d total interfaces\n", total);
    }

    CreateClientPipe();
    std::thread pipeThread{[]() {
        while (true) {
            Steam::ClientPipe()->ProcessMessages();

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
        }
    }};
#endif

    printf("Server started...\n");

    // Dont try and exit
    serverThread.join();

    return 0;
}

#include "../steam/rpc.hh"
