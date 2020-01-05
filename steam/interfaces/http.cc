#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientHTTP.h"
}

template <bool isServer>
class ClientHTTP : public Reference::IClientHTTP {
public:
    UserHandle userHandle;
    ClientHTTP(UserHandle h) : userHandle(h) {}

    unknown_ret CreateHTTPRequest(EHTTPMethod, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetHTTPRequestContextValue(unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret SetHTTPRequestNetworkActivityTimeout(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetHTTPRequestHeaderValue(unsigned int, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetHTTPRequestGetOrPostParameter(unsigned int, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret SendHTTPRequest(unsigned int, unsigned long long *) override {
        return unknown_ret();
    }
    unknown_ret SendHTTPRequestAndStreamResponse(unsigned int, unsigned long long *) override {
        return unknown_ret();
    }
    unknown_ret DeferHTTPRequest(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret PrioritizeHTTPRequest(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CancelHTTPRequest(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetHTTPResponseHeaderSize(unsigned int, char const *, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetHTTPResponseHeaderValue(unsigned int, char const *, unsigned char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetHTTPResponseBodySize(unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetHTTPResponseBodyData(unsigned int, unsigned char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetHTTPStreamingResponseBodyData(unsigned int, unsigned int, unsigned char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret ReleaseHTTPRequest(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetHTTPDownloadProgressPct(unsigned int, float *) override {
        return unknown_ret();
    }
    unknown_ret SetHTTPRequestRawPostBody(unsigned int, char const *, unsigned char *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CreateCookieContainer(bool) override {
        return unknown_ret();
    }
    unknown_ret ReleaseCookieContainer(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetCookie(unsigned int, char const *, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetHTTPRequestCookieContainer(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetHTTPRequestUserAgentInfo(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetHTTPRequestRequiresVerifiedCertificate(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetHTTPRequestAbsoluteTimeoutMS(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetHTTPRequestWasTimedOut(unsigned int, bool *) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientHTTP, "SteamHTTP");

using IClientHTTP = ClientHTTP<false>;

AdaptDeclare(ISteamHTTP003);
AdaptDefine(ISteamHTTP003, IClientHTTP, "SteamHTTP003") = {
    AdaptPassThrough(IClientHTTP::CreateHTTPRequest),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestContextValue),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestNetworkActivityTimeout),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestHeaderValue),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestGetOrPostParameter),
    AdaptPassThrough(IClientHTTP::SendHTTPRequest),
    AdaptPassThrough(IClientHTTP::SendHTTPRequestAndStreamResponse),
    AdaptPassThrough(IClientHTTP::DeferHTTPRequest),
    AdaptPassThrough(IClientHTTP::PrioritizeHTTPRequest),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseHeaderSize),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseHeaderValue),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseBodySize),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseBodyData),
    AdaptPassThrough(IClientHTTP::GetHTTPStreamingResponseBodyData),
    AdaptPassThrough(IClientHTTP::ReleaseHTTPRequest),
    AdaptPassThrough(IClientHTTP::GetHTTPDownloadProgressPct),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestRawPostBody),
    AdaptPassThrough(IClientHTTP::CreateCookieContainer),
    AdaptPassThrough(IClientHTTP::ReleaseCookieContainer),
    AdaptPassThrough(IClientHTTP::SetCookie),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestCookieContainer),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestUserAgentInfo),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestRequiresVerifiedCertificate),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestAbsoluteTimeoutMS),
    AdaptPassThrough(IClientHTTP::GetHTTPRequestWasTimedOut),
};
AdaptDeclare(ISteamHTTP002);
AdaptDefine(ISteamHTTP002, IClientHTTP, "SteamHTTP002") = {
    AdaptPassThrough(IClientHTTP::CreateHTTPRequest),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestContextValue),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestNetworkActivityTimeout),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestHeaderValue),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestGetOrPostParameter),
    AdaptPassThrough(IClientHTTP::SendHTTPRequest),
    AdaptPassThrough(IClientHTTP::SendHTTPRequestAndStreamResponse),
    AdaptPassThrough(IClientHTTP::DeferHTTPRequest),
    AdaptPassThrough(IClientHTTP::PrioritizeHTTPRequest),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseHeaderSize),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseHeaderValue),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseBodySize),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseBodyData),
    AdaptPassThrough(IClientHTTP::GetHTTPStreamingResponseBodyData),
    AdaptPassThrough(IClientHTTP::ReleaseHTTPRequest),
    AdaptPassThrough(IClientHTTP::GetHTTPDownloadProgressPct),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestRawPostBody),
    AdaptPassThrough(IClientHTTP::CreateCookieContainer),
    AdaptPassThrough(IClientHTTP::ReleaseCookieContainer),
    AdaptPassThrough(IClientHTTP::SetCookie),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestCookieContainer),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestUserAgentInfo),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestRequiresVerifiedCertificate),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestAbsoluteTimeoutMS),
    AdaptPassThrough(IClientHTTP::GetHTTPRequestWasTimedOut),
};
AdaptDeclare(ISteamHTTP001);
AdaptDefine(ISteamHTTP001, IClientHTTP, "SteamHTTP001") = {
    AdaptPassThrough(IClientHTTP::CreateHTTPRequest),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestContextValue),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestNetworkActivityTimeout),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestHeaderValue),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestGetOrPostParameter),
    AdaptPassThrough(IClientHTTP::SendHTTPRequest),
    AdaptPassThrough(IClientHTTP::DeferHTTPRequest),
    AdaptPassThrough(IClientHTTP::PrioritizeHTTPRequest),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseHeaderSize),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseHeaderValue),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseBodySize),
    AdaptPassThrough(IClientHTTP::GetHTTPResponseBodyData),
    AdaptPassThrough(IClientHTTP::ReleaseHTTPRequest),
    AdaptPassThrough(IClientHTTP::GetHTTPDownloadProgressPct),
    AdaptPassThrough(IClientHTTP::SetHTTPRequestRawPostBody),
};
