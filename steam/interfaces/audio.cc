#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientAudio.h"
}

template <bool isServer>
class ClientAudio : public Reference::IClientAudio {
public:
    UserHandle userHandle;
    ClientAudio(UserHandle h) : userHandle(h) {}

    unknown_ret StartVoiceRecording() override {
        return unknown_ret();
    }
    unknown_ret StopVoiceRecording() override {
        return unknown_ret();
    }
    unknown_ret ResetVoiceRecording() override {
        return unknown_ret();
    }
    unknown_ret GetAvailableVoice(unsigned int *, unsigned int *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetVoice(bool, void *, unsigned int, unsigned int *, bool, void *, unsigned int, unsigned int *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetCompressedVoice(void *, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret DecompressVoice(void const *, unsigned int, void *, unsigned int, unsigned int *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetVoiceOptimalSampleRate() override {
        return unknown_ret();
    }
    unknown_ret BAppUsesVoice(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetGameSystemVolume() override {
        return unknown_ret();
    }
    unknown_ret SetGameSystemVolume(float) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientAudio, "SteamAudio");

using IClientAudio = ClientAudio<false>;
