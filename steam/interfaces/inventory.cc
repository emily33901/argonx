
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClientInventory.h"
}

template <bool isServer>
class ClientInventory : public Reference::IClientInventory {
public:
    UserHandle userHandle;
    ClientInventory(UserHandle h) : userHandle(h) {}

    unknown_ret GetResultStatus(int) override {
        return unknown_ret();
    }
    unknown_ret DestroyResult(int) override {
        return unknown_ret();
    }
    unknown_ret GetResultItems(int, SteamItemDetails_t *, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetResultItemProperty(int, unsigned int, char const *, char *, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetResultTimestamp(int) override {
        return unknown_ret();
    }
    unknown_ret CheckResultSteamID(int, CSteamID) override {
        return unknown_ret();
    }
    unknown_ret SerializeResult(int, void *, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret DeserializeResult(int *, void const *, unsigned int, bool) override {
        return unknown_ret();
    }
    unknown_ret GetAllItems(int *) override {
        return unknown_ret();
    }
    unknown_ret GetItemsByID(int *, unsigned long long const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GenerateItems(int *, int const *, unsigned int, unsigned int const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret AddPromoItems(int *, int const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret ConsumeItem(int *, unsigned long long, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret ExchangeItems(int *, int const *, unsigned int, unsigned int const *, unsigned int, unsigned long long const *, unsigned int, unsigned int const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret TransferItemQuantity(int *, unsigned long long, unsigned int, unsigned long long) override {
        return unknown_ret();
    }
    unknown_ret SendItemDropHeartbeat() override {
        return unknown_ret();
    }
    unknown_ret TriggerItemDrop(int *, int) override {
        return unknown_ret();
    }
    unknown_ret TradeItems(int *, CSteamID, unsigned long long const *, unsigned int, unsigned int const *, unsigned int, unsigned long long const *, unsigned int, unsigned int const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret LoadItemDefinitions() override {
        return unknown_ret();
    }
    unknown_ret GetItemDefinitionIDs(int *, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret GetItemDefinitionProperty(int, char const *, char *, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret RequestEligiblePromoItemDefinitionsIDs(CSteamID) override {
        return unknown_ret();
    }
    unknown_ret GetEligiblePromoItemDefinitionIDs(CSteamID, int *, unsigned int, unsigned int *) override {
        return unknown_ret();
    }
    unknown_ret StartPurchase(int const *, unsigned int, unsigned int const *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret RequestPrices() override {
        return unknown_ret();
    }
    unknown_ret GetNumItemsWithPrices() override {
        return unknown_ret();
    }
    unknown_ret GetItemsWithPrices(int *, unsigned long long *, unsigned long long *, unsigned int) override {
        return unknown_ret();
    }
    unknown_ret GetItemPrice(int, unsigned long long *, unsigned long long *) override {
        return unknown_ret();
    }
    unknown_ret StartUpdateProperties() override {
        return unknown_ret();
    }
    unknown_ret RemoveProperty(unsigned long long, unsigned long long, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetProperty(unsigned long long, unsigned long long, char const *, char const *) override {
        return unknown_ret();
    }
    unknown_ret SetProperty(unsigned long long, unsigned long long, char const *, bool) override {
        return unknown_ret();
    }
    unknown_ret SetProperty(unsigned long long, unsigned long long, char const *, long long) override {
        return unknown_ret();
    }
    unknown_ret SetProperty(unsigned long long, unsigned long long, char const *, float) override {
        return unknown_ret();
    }
    unknown_ret SubmitUpdateProperties(unsigned long long, int *) override {
        return unknown_ret();
    }
};

AdaptExposeClientServer(ClientInventory, "SteamInventory");

using IClientInventory = ClientInventory<false>;

AdaptDeclare(ISteamInventory003);
AdaptDefine(ISteamInventory003, IClientInventory, "SteamInventory003") = {
    AdaptPassThrough(IClientInventory::GetResultStatus),
    AdaptPassThrough(IClientInventory::GetResultItems),
    AdaptPassThrough(IClientInventory::GetResultItemProperty),
    AdaptPassThrough(IClientInventory::GetResultTimestamp),
    AdaptPassThrough(IClientInventory::CheckResultSteamID),
    AdaptPassThrough(IClientInventory::DestroyResult),
    AdaptPassThrough(IClientInventory::GetAllItems),
    AdaptPassThrough(IClientInventory::GetItemsByID),
    AdaptPassThrough(IClientInventory::SerializeResult),
    AdaptPassThrough(IClientInventory::DeserializeResult),
    AdaptPassThrough(IClientInventory::GenerateItems),
    AdaptEmpty(IClientInventory::GrantPromoItems),
    AdaptEmpty(IClientInventory::AddPromoItem),
    AdaptPassThrough(IClientInventory::AddPromoItems),
    AdaptPassThrough(IClientInventory::ConsumeItem),
    AdaptPassThrough(IClientInventory::ExchangeItems),
    AdaptPassThrough(IClientInventory::TransferItemQuantity),
    AdaptPassThrough(IClientInventory::SendItemDropHeartbeat),
    AdaptPassThrough(IClientInventory::TriggerItemDrop),
    AdaptPassThrough(IClientInventory::TradeItems),
    AdaptPassThrough(IClientInventory::LoadItemDefinitions),
    AdaptPassThrough(IClientInventory::GetItemDefinitionIDs),
    AdaptPassThrough(IClientInventory::GetItemDefinitionProperty),
    AdaptPassThrough(IClientInventory::RequestEligiblePromoItemDefinitionsIDs),
    AdaptPassThrough(IClientInventory::GetEligiblePromoItemDefinitionIDs),
    AdaptPassThrough(IClientInventory::StartPurchase),
    AdaptPassThrough(IClientInventory::RequestPrices),
    AdaptPassThrough(IClientInventory::GetNumItemsWithPrices),
    AdaptPassThrough(IClientInventory::GetItemsWithPrices),
    AdaptPassThrough(IClientInventory::GetItemPrice),
    AdaptPassThrough(IClientInventory::StartUpdateProperties),
    AdaptPassThrough(IClientInventory::RemoveProperty),
    AdaptOverload(unknown_ret(IClientInventory::*)(unsigned long long, unsigned long long, char const *, char const *), IClientInventory::SetProperty),
    AdaptOverload(unknown_ret(IClientInventory::*)(unsigned long long, unsigned long long, char const *, bool), IClientInventory::SetProperty),
    AdaptOverload(unknown_ret(IClientInventory::*)(unsigned long long, unsigned long long, char const *, long long), IClientInventory::SetProperty),
    AdaptOverload(unknown_ret(IClientInventory::*)(unsigned long long, unsigned long long, char const *, float), IClientInventory::SetProperty),
    AdaptPassThrough(IClientInventory::SubmitUpdateProperties),
};
AdaptDeclare(ISteamInventory002);
AdaptDefine(ISteamInventory002, IClientInventory, "SteamInventory002") = {
    AdaptPassThrough(IClientInventory::GetResultStatus),
    AdaptPassThrough(IClientInventory::GetResultItems),
    AdaptPassThrough(IClientInventory::GetResultItemProperty),
    AdaptPassThrough(IClientInventory::GetResultTimestamp),
    AdaptPassThrough(IClientInventory::CheckResultSteamID),
    AdaptPassThrough(IClientInventory::DestroyResult),
    AdaptPassThrough(IClientInventory::GetAllItems),
    AdaptPassThrough(IClientInventory::GetItemsByID),
    AdaptPassThrough(IClientInventory::SerializeResult),
    AdaptPassThrough(IClientInventory::DeserializeResult),
    AdaptPassThrough(IClientInventory::GenerateItems),
    AdaptEmpty(IClientInventory::GrantPromoItems),
    AdaptEmpty(IClientInventory::AddPromoItem),
    AdaptPassThrough(IClientInventory::AddPromoItems),
    AdaptPassThrough(IClientInventory::ConsumeItem),
    AdaptPassThrough(IClientInventory::ExchangeItems),
    AdaptPassThrough(IClientInventory::TransferItemQuantity),
    AdaptPassThrough(IClientInventory::SendItemDropHeartbeat),
    AdaptPassThrough(IClientInventory::TriggerItemDrop),
    AdaptPassThrough(IClientInventory::TradeItems),
    AdaptPassThrough(IClientInventory::LoadItemDefinitions),
    AdaptPassThrough(IClientInventory::GetItemDefinitionIDs),
    AdaptPassThrough(IClientInventory::GetItemDefinitionProperty),
    AdaptPassThrough(IClientInventory::RequestEligiblePromoItemDefinitionsIDs),
    AdaptPassThrough(IClientInventory::GetEligiblePromoItemDefinitionIDs),
    AdaptPassThrough(IClientInventory::StartPurchase),
    AdaptPassThrough(IClientInventory::RequestPrices),
    AdaptPassThrough(IClientInventory::GetNumItemsWithPrices),
    AdaptPassThrough(IClientInventory::GetItemsWithPrices),
    AdaptPassThrough(IClientInventory::GetItemPrice),
    AdaptPassThrough(IClientInventory::StartUpdateProperties),
    AdaptPassThrough(IClientInventory::RemoveProperty),
    AdaptOverload(unknown_ret(IClientInventory::*)(unsigned long long, unsigned long long, char const *, char const *), IClientInventory::SetProperty),
    AdaptOverload(unknown_ret(IClientInventory::*)(unsigned long long, unsigned long long, char const *, bool), IClientInventory::SetProperty),
    AdaptOverload(unknown_ret(IClientInventory::*)(unsigned long long, unsigned long long, char const *, long long), IClientInventory::SetProperty),
    AdaptOverload(unknown_ret(IClientInventory::*)(unsigned long long, unsigned long long, char const *, float), IClientInventory::SetProperty),
    AdaptPassThrough(IClientInventory::SubmitUpdateProperties),
};
AdaptDeclare(ISteamInventory001);
AdaptDefine(ISteamInventory001, IClientInventory, "SteamInventory001") = {
    AdaptPassThrough(IClientInventory::GetResultStatus),
    AdaptPassThrough(IClientInventory::GetResultItems),
    AdaptPassThrough(IClientInventory::GetResultTimestamp),
    AdaptPassThrough(IClientInventory::CheckResultSteamID),
    AdaptPassThrough(IClientInventory::DestroyResult),
    AdaptPassThrough(IClientInventory::GetAllItems),
    AdaptPassThrough(IClientInventory::GetItemsByID),
    AdaptPassThrough(IClientInventory::SerializeResult),
    AdaptPassThrough(IClientInventory::DeserializeResult),
    AdaptPassThrough(IClientInventory::GenerateItems),
    AdaptEmpty(IClientInventory::GrantPromoItems),
    AdaptEmpty(IClientInventory::AddPromoItem),
    AdaptPassThrough(IClientInventory::AddPromoItems),
    AdaptPassThrough(IClientInventory::ConsumeItem),
    AdaptPassThrough(IClientInventory::ExchangeItems),
    AdaptPassThrough(IClientInventory::TransferItemQuantity),
    AdaptPassThrough(IClientInventory::SendItemDropHeartbeat),
    AdaptPassThrough(IClientInventory::TriggerItemDrop),
    AdaptPassThrough(IClientInventory::TradeItems),
    AdaptPassThrough(IClientInventory::LoadItemDefinitions),
    AdaptPassThrough(IClientInventory::GetItemDefinitionIDs),
    AdaptPassThrough(IClientInventory::GetItemDefinitionProperty),
    AdaptPassThrough(IClientInventory::RequestEligiblePromoItemDefinitionsIDs),
    AdaptPassThrough(IClientInventory::GetEligiblePromoItemDefinitionIDs),
};
