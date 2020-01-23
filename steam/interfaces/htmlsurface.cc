
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientHTMLSurface.h"
}

template <bool isServer>
class ClientHTMLSurface : public Reference::IClientHTMLSurface {
public:
    UserHandle userHandle;
    ClientHTMLSurface(UserHandle h) : userHandle(h) {}

    unknown_ret __Destructor1() override {
        return unknown_ret();
    }
#ifdef ARGONX_UNIX
    unknown_ret __Destructor2() override {
        return unknown_ret();
    }
#endif
    unknown_ret Init() override {
        return unknown_ret();
    }
    unknown_ret Shutdown() override {
        return unknown_ret();
    }
    unknown_ret CreateBrowser(char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret RemoveBrowser(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret AllowStartRequest(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret LoadURL(unsigned int, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetSize(unsigned int, unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret StopLoad(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret Reload(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GoBack(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GoForward(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret AddHeader(unsigned int, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret ExecuteJavascript(unsigned int, char const *) override {
        return unknown_ret();
    }
    unknown_ret MouseUp(unsigned int, ISteamHTMLSurface::EHTMLMouseButton) override {
        return unknown_ret();
    }
    unknown_ret MouseDown(unsigned int, ISteamHTMLSurface::EHTMLMouseButton) override {
        return unknown_ret();
    }
    unknown_ret MouseDoubleClick(unsigned int, ISteamHTMLSurface::EHTMLMouseButton) override {
        return unknown_ret();
    }
    unknown_ret MouseMove(unsigned int, int, int) override {
        return unknown_ret();
    }
    unknown_ret MouseWheel(unsigned int, int) override {
        return unknown_ret();
    }
    unknown_ret KeyDown(unsigned int, unsigned int, ISteamHTMLSurface::EHTMLKeyModifiers, bool) override {
        return unknown_ret();
    }
    unknown_ret KeyUp(unsigned int, unsigned int, ISteamHTMLSurface::EHTMLKeyModifiers) override {
        return unknown_ret();
    }
    unknown_ret KeyChar(unsigned int, unsigned int, ISteamHTMLSurface::EHTMLKeyModifiers) override {
        return unknown_ret();
    }
    unknown_ret SetHorizontalScroll(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetVerticalScroll(unsigned int, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret SetKeyFocus(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret ViewSource(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret CopyToClipboard(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret PasteFromClipboard(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret Find(unsigned int, char const *, bool, bool) override {
        return unknown_ret();
    }
    unknown_ret StopFind(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetLinkAtPosition(unsigned int, int, int) override {
        return unknown_ret();
    }
    unknown_ret JSDialogResponse(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret FileLoadDialogResponse(unsigned int, char const **) override {
        return unknown_ret();
    }
    unknown_ret SetCookie(char const *, char const *, char const *, char const *, unsigned int, bool, bool) override {
        return unknown_ret();
    }
    unknown_ret SetPageScaleFactor(unsigned int, float, int, int) override {
        return unknown_ret();
    }
    unknown_ret SetBackgroundMode(unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret SetDPIScalingFactor(unsigned int, float) override {
        return unknown_ret();
    }
    unknown_ret OpenDeveloperTools(unsigned int) override {
        return unknown_ret();
    }
    unknown_ret Validate(CValidator &, char const *) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientHTMLSurface, "SteamHTMLSurface");

using IClientHTMLSurface = ClientHTMLSurface<false>;

AdaptDeclare(ISteamHTMLSurface004);
AdaptDefine(ISteamHTMLSurface004, IClientHTMLSurface, "SteamHTMLSurface004") = {
    AdaptPassThrough(IClientHTMLSurface::__Destructor1),
#ifdef ARGONX_UNIX
    AdaptPassThrough(IClientHTMLSurface::__Destructor2),
#endif
    AdaptPassThrough(IClientHTMLSurface::Init),
    AdaptPassThrough(IClientHTMLSurface::Shutdown),
    AdaptPassThrough(IClientHTMLSurface::CreateBrowser),
    AdaptPassThrough(IClientHTMLSurface::RemoveBrowser),
    AdaptPassThrough(IClientHTMLSurface::LoadURL),
    AdaptPassThrough(IClientHTMLSurface::SetSize),
    AdaptPassThrough(IClientHTMLSurface::StopLoad),
    AdaptPassThrough(IClientHTMLSurface::Reload),
    AdaptPassThrough(IClientHTMLSurface::GoBack),
    AdaptPassThrough(IClientHTMLSurface::GoForward),
    AdaptPassThrough(IClientHTMLSurface::AddHeader),
    AdaptPassThrough(IClientHTMLSurface::ExecuteJavascript),
    AdaptPassThrough(IClientHTMLSurface::MouseUp),
    AdaptPassThrough(IClientHTMLSurface::MouseDown),
    AdaptPassThrough(IClientHTMLSurface::MouseDoubleClick),
    AdaptPassThrough(IClientHTMLSurface::MouseMove),
    AdaptPassThrough(IClientHTMLSurface::MouseWheel),
    AdaptPassThrough(IClientHTMLSurface::KeyDown),
    AdaptPassThrough(IClientHTMLSurface::KeyUp),
    AdaptPassThrough(IClientHTMLSurface::KeyChar),
    AdaptPassThrough(IClientHTMLSurface::SetHorizontalScroll),
    AdaptPassThrough(IClientHTMLSurface::SetVerticalScroll),
    AdaptPassThrough(IClientHTMLSurface::SetKeyFocus),
    AdaptPassThrough(IClientHTMLSurface::ViewSource),
    AdaptPassThrough(IClientHTMLSurface::CopyToClipboard),
    AdaptPassThrough(IClientHTMLSurface::PasteFromClipboard),
    AdaptPassThrough(IClientHTMLSurface::Find),
    AdaptPassThrough(IClientHTMLSurface::StopFind),
    AdaptPassThrough(IClientHTMLSurface::GetLinkAtPosition),
    AdaptPassThrough(IClientHTMLSurface::SetCookie),
    AdaptPassThrough(IClientHTMLSurface::SetPageScaleFactor),
    AdaptPassThrough(IClientHTMLSurface::SetBackgroundMode),
    AdaptPassThrough(IClientHTMLSurface::SetDPIScalingFactor),
    AdaptPassThrough(IClientHTMLSurface::AllowStartRequest),
    AdaptPassThrough(IClientHTMLSurface::JSDialogResponse),
    AdaptPassThrough(IClientHTMLSurface::FileLoadDialogResponse),
};
AdaptDeclare(ISteamHTMLSurface002);
AdaptDefine(ISteamHTMLSurface002, IClientHTMLSurface, "SteamHTMLSurface002") = {
    AdaptPassThrough(IClientHTMLSurface::__Destructor1),
#ifdef ARGONX_UNIX
    AdaptPassThrough(IClientHTMLSurface::__Destructor2),
#endif
    AdaptPassThrough(IClientHTMLSurface::Init),
    AdaptPassThrough(IClientHTMLSurface::Shutdown),
    AdaptPassThrough(IClientHTMLSurface::CreateBrowser),
    AdaptPassThrough(IClientHTMLSurface::RemoveBrowser),
    AdaptPassThrough(IClientHTMLSurface::LoadURL),
    AdaptPassThrough(IClientHTMLSurface::SetSize),
    AdaptPassThrough(IClientHTMLSurface::StopLoad),
    AdaptPassThrough(IClientHTMLSurface::Reload),
    AdaptPassThrough(IClientHTMLSurface::GoBack),
    AdaptPassThrough(IClientHTMLSurface::GoForward),
    AdaptPassThrough(IClientHTMLSurface::AddHeader),
    AdaptPassThrough(IClientHTMLSurface::ExecuteJavascript),
    AdaptPassThrough(IClientHTMLSurface::MouseUp),
    AdaptPassThrough(IClientHTMLSurface::MouseDown),
    AdaptPassThrough(IClientHTMLSurface::MouseDoubleClick),
    AdaptPassThrough(IClientHTMLSurface::MouseMove),
    AdaptPassThrough(IClientHTMLSurface::MouseWheel),
    AdaptPassThrough(IClientHTMLSurface::KeyDown),
    AdaptPassThrough(IClientHTMLSurface::KeyUp),
    AdaptPassThrough(IClientHTMLSurface::KeyChar),
    AdaptPassThrough(IClientHTMLSurface::SetHorizontalScroll),
    AdaptPassThrough(IClientHTMLSurface::SetVerticalScroll),
    AdaptPassThrough(IClientHTMLSurface::SetKeyFocus),
    AdaptPassThrough(IClientHTMLSurface::ViewSource),
    AdaptPassThrough(IClientHTMLSurface::CopyToClipboard),
    AdaptPassThrough(IClientHTMLSurface::PasteFromClipboard),
    AdaptPassThrough(IClientHTMLSurface::Find),
    AdaptPassThrough(IClientHTMLSurface::StopFind),
    AdaptPassThrough(IClientHTMLSurface::GetLinkAtPosition),
    AdaptPassThrough(IClientHTMLSurface::SetCookie),
    AdaptPassThrough(IClientHTMLSurface::SetPageScaleFactor),
    AdaptPassThrough(IClientHTMLSurface::AllowStartRequest),
    AdaptPassThrough(IClientHTMLSurface::JSDialogResponse),
    AdaptPassThrough(IClientHTMLSurface::FileLoadDialogResponse),
};
AdaptDeclare(ISteamHTMLSurface005);
AdaptDefine(ISteamHTMLSurface005, IClientHTMLSurface, "SteamHTMLSurface005") = {
    AdaptPassThrough(IClientHTMLSurface::__Destructor1),
#ifdef ARGONX_UNIX
    AdaptPassThrough(IClientHTMLSurface::__Destructor2),
#endif
    AdaptPassThrough(IClientHTMLSurface::Init),
    AdaptPassThrough(IClientHTMLSurface::Shutdown),
    AdaptPassThrough(IClientHTMLSurface::CreateBrowser),
    AdaptPassThrough(IClientHTMLSurface::RemoveBrowser),
    AdaptPassThrough(IClientHTMLSurface::LoadURL),
    AdaptPassThrough(IClientHTMLSurface::SetSize),
    AdaptPassThrough(IClientHTMLSurface::StopLoad),
    AdaptPassThrough(IClientHTMLSurface::Reload),
    AdaptPassThrough(IClientHTMLSurface::GoBack),
    AdaptPassThrough(IClientHTMLSurface::GoForward),
    AdaptPassThrough(IClientHTMLSurface::AddHeader),
    AdaptPassThrough(IClientHTMLSurface::ExecuteJavascript),
    AdaptPassThrough(IClientHTMLSurface::MouseUp),
    AdaptPassThrough(IClientHTMLSurface::MouseDown),
    AdaptPassThrough(IClientHTMLSurface::MouseDoubleClick),
    AdaptPassThrough(IClientHTMLSurface::MouseMove),
    AdaptPassThrough(IClientHTMLSurface::MouseWheel),
    AdaptPassThrough(IClientHTMLSurface::KeyDown),
    AdaptPassThrough(IClientHTMLSurface::KeyUp),
    AdaptPassThrough(IClientHTMLSurface::KeyChar),
    AdaptPassThrough(IClientHTMLSurface::SetHorizontalScroll),
    AdaptPassThrough(IClientHTMLSurface::SetVerticalScroll),
    AdaptPassThrough(IClientHTMLSurface::SetKeyFocus),
    AdaptPassThrough(IClientHTMLSurface::ViewSource),
    AdaptPassThrough(IClientHTMLSurface::CopyToClipboard),
    AdaptPassThrough(IClientHTMLSurface::PasteFromClipboard),
    AdaptPassThrough(IClientHTMLSurface::Find),
    AdaptPassThrough(IClientHTMLSurface::StopFind),
    AdaptPassThrough(IClientHTMLSurface::GetLinkAtPosition),
    AdaptPassThrough(IClientHTMLSurface::SetCookie),
    AdaptPassThrough(IClientHTMLSurface::SetPageScaleFactor),
    AdaptPassThrough(IClientHTMLSurface::SetBackgroundMode),
    AdaptPassThrough(IClientHTMLSurface::SetDPIScalingFactor),
    AdaptPassThrough(IClientHTMLSurface::OpenDeveloperTools),
    AdaptPassThrough(IClientHTMLSurface::AllowStartRequest),
    AdaptPassThrough(IClientHTMLSurface::JSDialogResponse),
    AdaptPassThrough(IClientHTMLSurface::FileLoadDialogResponse),
};
AdaptDeclare(ISteamHTMLSurface003);
AdaptDefine(ISteamHTMLSurface003, IClientHTMLSurface, "SteamHTMLSurface003") = {
    AdaptPassThrough(IClientHTMLSurface::__Destructor1),
#ifdef ARGONX_UNIX
    AdaptPassThrough(IClientHTMLSurface::__Destructor2),
#endif
    AdaptPassThrough(IClientHTMLSurface::Init),
    AdaptPassThrough(IClientHTMLSurface::Shutdown),
    AdaptPassThrough(IClientHTMLSurface::CreateBrowser),
    AdaptPassThrough(IClientHTMLSurface::RemoveBrowser),
    AdaptPassThrough(IClientHTMLSurface::LoadURL),
    AdaptPassThrough(IClientHTMLSurface::SetSize),
    AdaptPassThrough(IClientHTMLSurface::StopLoad),
    AdaptPassThrough(IClientHTMLSurface::Reload),
    AdaptPassThrough(IClientHTMLSurface::GoBack),
    AdaptPassThrough(IClientHTMLSurface::GoForward),
    AdaptPassThrough(IClientHTMLSurface::AddHeader),
    AdaptPassThrough(IClientHTMLSurface::ExecuteJavascript),
    AdaptPassThrough(IClientHTMLSurface::MouseUp),
    AdaptPassThrough(IClientHTMLSurface::MouseDown),
    AdaptPassThrough(IClientHTMLSurface::MouseDoubleClick),
    AdaptPassThrough(IClientHTMLSurface::MouseMove),
    AdaptPassThrough(IClientHTMLSurface::MouseWheel),
    AdaptPassThrough(IClientHTMLSurface::KeyDown),
    AdaptPassThrough(IClientHTMLSurface::KeyUp),
    AdaptPassThrough(IClientHTMLSurface::KeyChar),
    AdaptPassThrough(IClientHTMLSurface::SetHorizontalScroll),
    AdaptPassThrough(IClientHTMLSurface::SetVerticalScroll),
    AdaptPassThrough(IClientHTMLSurface::SetKeyFocus),
    AdaptPassThrough(IClientHTMLSurface::ViewSource),
    AdaptPassThrough(IClientHTMLSurface::CopyToClipboard),
    AdaptPassThrough(IClientHTMLSurface::PasteFromClipboard),
    AdaptPassThrough(IClientHTMLSurface::Find),
    AdaptPassThrough(IClientHTMLSurface::StopFind),
    AdaptPassThrough(IClientHTMLSurface::GetLinkAtPosition),
    AdaptPassThrough(IClientHTMLSurface::SetCookie),
    AdaptPassThrough(IClientHTMLSurface::SetPageScaleFactor),
    AdaptPassThrough(IClientHTMLSurface::SetBackgroundMode),
    AdaptPassThrough(IClientHTMLSurface::AllowStartRequest),
    AdaptPassThrough(IClientHTMLSurface::JSDialogResponse),
    AdaptPassThrough(IClientHTMLSurface::FileLoadDialogResponse),
};
AdaptDeclare(ISteamHTMLSurface001);
AdaptDefine(ISteamHTMLSurface001, IClientHTMLSurface, "SteamHTMLSurface001") = {
    AdaptPassThrough(IClientHTMLSurface::__Destructor1),
#ifdef ARGONX_UNIX
    AdaptPassThrough(IClientHTMLSurface::__Destructor2),
#endif
    AdaptPassThrough(IClientHTMLSurface::Init),
    AdaptPassThrough(IClientHTMLSurface::Shutdown),
    AdaptPassThrough(IClientHTMLSurface::CreateBrowser),
    AdaptPassThrough(IClientHTMLSurface::RemoveBrowser),
    AdaptPassThrough(IClientHTMLSurface::LoadURL),
    AdaptPassThrough(IClientHTMLSurface::SetSize),
    AdaptPassThrough(IClientHTMLSurface::StopLoad),
    AdaptPassThrough(IClientHTMLSurface::Reload),
    AdaptPassThrough(IClientHTMLSurface::GoBack),
    AdaptPassThrough(IClientHTMLSurface::GoForward),
    AdaptPassThrough(IClientHTMLSurface::AddHeader),
    AdaptPassThrough(IClientHTMLSurface::ExecuteJavascript),
    AdaptPassThrough(IClientHTMLSurface::MouseUp),
    AdaptPassThrough(IClientHTMLSurface::MouseDown),
    AdaptPassThrough(IClientHTMLSurface::MouseDoubleClick),
    AdaptPassThrough(IClientHTMLSurface::MouseMove),
    AdaptPassThrough(IClientHTMLSurface::MouseWheel),
    AdaptPassThrough(IClientHTMLSurface::KeyDown),
    AdaptPassThrough(IClientHTMLSurface::KeyUp),
    AdaptPassThrough(IClientHTMLSurface::KeyChar),
    AdaptPassThrough(IClientHTMLSurface::SetHorizontalScroll),
    AdaptPassThrough(IClientHTMLSurface::SetVerticalScroll),
    AdaptPassThrough(IClientHTMLSurface::SetKeyFocus),
    AdaptPassThrough(IClientHTMLSurface::ViewSource),
    AdaptPassThrough(IClientHTMLSurface::CopyToClipboard),
    AdaptPassThrough(IClientHTMLSurface::PasteFromClipboard),
    AdaptPassThrough(IClientHTMLSurface::Find),
    AdaptPassThrough(IClientHTMLSurface::StopFind),
    AdaptPassThrough(IClientHTMLSurface::GetLinkAtPosition),
    AdaptPassThrough(IClientHTMLSurface::AllowStartRequest),
    AdaptPassThrough(IClientHTMLSurface::JSDialogResponse),
    AdaptPassThrough(IClientHTMLSurface::FileLoadDialogResponse),
};
