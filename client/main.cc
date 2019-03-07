#include <precompiled.hh>

#include <thread>

#include "../steam/interfaces/helpers.hh"

#include "ipc.hh"

class ISteamUtils009 {
public:
    virtual uptr GetSecondsSinceAppActive() = 0;

    virtual void pad0() = 0;
    virtual void pad1() = 0;
    virtual void pad2() = 0;

    virtual const char *GetIPCountry()                                                = 0;
    virtual uptr        GetImageSize(int imgHandle, unsigned int *w, unsigned int *h) = 0;
    virtual uptr        GetImageRGBA(int imgHandle, u8 *bufferOut, u32 maxOut)        = 0;

    virtual void pad6()  = 0;
    virtual void pad7()  = 0;
    virtual void pad8()  = 0;
    virtual void pad9()  = 0;
    virtual void pad10() = 0;

    virtual uptr GetAPICallFailureReason(unsigned long long) = 0;

    virtual void pad11() = 0;
    virtual void pad12() = 0;
    virtual void pad13() = 0;
    virtual void pad14() = 0;
    virtual void pad15() = 0;
    virtual void pad16() = 0;

    virtual uptr CheckFileSignature(const char *) = 0;
};

void CreateClientPipe() {
    Steam::SetClientPipe(new Pipe(false, "tcp://127.0.0.1:33901"));
    Steam::ClientPipe()->processMessage = [](Pipe::Target, u8 *data, u32 size) {
        printf("[clientpipe] size:%d\n", size);

        // Assume rpc job
        Buffer b;
        b.Write(std::make_pair(data, size));
        b.SetPos(0);

        auto jobId = b.Read<u64>();
        b.SetBaseAtCurPos();
        Steam::JobManager::PostResult(jobId, b);
    };
}


int main(const int argCount, const char **argStrings) {
    printf("Waiting for server...\n");
    CreateClientPipe();
    bool        running = true;
    std::thread pipeThread{[&running]() {
        while (running) {
            Steam::ClientPipe()->ProcessMessages();

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
        }
    }};

    void *clientUtils = Steam::CreateInterfaceWithUser("SteamUtils009", 0);
    auto utils             = (ISteamUtils009 *)clientUtils;

    uptr r;

#if 0
#endif
    r = utils->GetSecondsSinceAppActive();
    printf("r is %ld\n", r);
    r = utils->GetAPICallFailureReason(0xCCFFCCFFAABBAABB);
    printf("r is %ld\n", r);

    r = utils->CheckFileSignature("wow nice meme");
    printf("r is %ld\n", r);

    const char *country = utils->GetIPCountry();
    printf("country is %s\n", country);
    u32 w, h;
    utils->GetImageSize(0, &w, &h);
    printf("w is %d, h is %d\n", w, h);

    u8 buffer[10];
    memset(buffer, 0xDE, sizeof(buffer));
    utils->GetImageRGBA(15, buffer, 10);
    buffer[9] = '\0';
    printf("Buffer is \"%s\"\n", buffer);
#if 0
#endif

    running = false;
    pipeThread.join();
}