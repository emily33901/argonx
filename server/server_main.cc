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
    Steam::SetServerPipe(new Pipe(true, "tcp://127.0.0.1:33901"));
    Steam::ServerPipe()->processMessage = [](Pipe::Target target, u8 *data, u32 size) {
        LOG_SCOPE_F(INFO, "Server message [%lu]", target);
        LOG_F(INFO, "size:%d", size);

        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        i64 jobId = b.Read<i64>();

        if (jobId < 0) {
            LOG_F(INFO, "Recieved non-call job %lld", jobId);
            // Non-call job
            auto header = b.Read<Steam::RpcNonCallHeader>();

            switch (header.t) {
            case Steam::RpcType::heartbeat: {
                LOG_F(INFO, "Recieved heartbeat");
                heartbeats[target] = std::chrono::system_clock::now();

                // Send it straight back
                // Steam::ServerPipe()->SendMessage(target, data, size);
            } break;
            case Steam::RpcType::disconnect: {
                LOG_F(INFO, "Recieved disconnect");
                heartbeats[target] = std::chrono::system_clock::now() - std::chrono::seconds(100000);

                // Show that we got the disconnect
                Steam::ServerPipe()->SendMessage(target, data, size);
            } break;
            }
        } else {
            Steam::RpcCallHeader header;
            b.ReadInto(header);

            LOG_F(INFO, "userHandle:%d", header.userHandle);

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

            LOG_F(INFO, "Target:%s index:%d", Steam::InterfaceName(header.targetInterface), header.functionIndex);

            // Paste the jobid back onto the front of the buffer and send it back
            b.SetPos(0);
            b.Write(jobId);

            Steam::ServerPipe()->SendMessage(target, b);
        }
    };
}

int main(int argCount, char **argStrings) {
    loguru::init(argCount, argStrings);

    // Put every log message in "everything.log":
    loguru::add_file("everything.log", loguru::Append, loguru::Verbosity_MAX);

    // Only log INFO, WARNING, ERROR and FATAL to "latest_readable.log":
    loguru::add_file("latest_readable.log", loguru::Truncate, loguru::Verbosity_INFO);

    // Only show most relevant things on stderr:
    loguru::g_stderr_verbosity = 1;

    CreateNoUserInterfaceStorage();

    CreateServerPipe();
    std::thread serverThread{
        []() {
            loguru::set_thread_name("server");
            std::vector<Pipe::Target> keysToErase;

            while (true) {
                keysToErase.clear();

                Steam::ServerPipe()->ProcessMessages();

                using namespace std::chrono_literals;
                std::this_thread::sleep_for(1ms);

                auto now = std::chrono::system_clock::now();

                for (auto &[k, v] : heartbeats) {
                    if ((now - v) > 2min) {
                        LOG_F(INFO, "Dropping client %d", k);
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
    LOG_F(INFO, "%d trampolines allocated (%d bytes)...",
           Steam::InterfaceHelpers::TAllocator()->NumAllocated(),
           Steam::InterfaceHelpers::TAllocator()->BytesAllocated());

    {
        u32 counter = 0;
        for (auto &p : Steam::RpcDispatches()) {
            LOG_F(INFO, "%d: %s", counter++, p.second);
        }
    }
    {
        extern Steam::InterfaceHelpers::InterfaceReg *GetInterfaceList();

        auto head  = GetInterfaceList();
        auto total = 0;

        for (auto cur = head; cur != nullptr; cur = cur->next) {
            total += 1;
            LOG_F(INFO, "[I%s] %s", cur->requiresUser ? "u" : " ", cur->name);
        }

        LOG_F(INFO, "[I] %d total interfaces", total);
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

    LOG_F(INFO, "Server started...");

    // Dont try and exit
    serverThread.join();

    return 0;
}

#include "../steam/rpc.hh"
