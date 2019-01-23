#include "precompiled.hh"

#include "../steam/interfaces/helpers.hh"

namespace {
class TestTarget {
    int basis;

public:
    TestTarget() {
        basis = 10;
    }

    virtual int GetBasis() {
        return basis;
    }

    virtual int AddToBasis(int n) {
        return basis += n;
    }

    virtual int SubFromBasis(int n1, int n2) {
        return basis -= n1 + n2;
    }
};

AdaptDeclare(Test001);
AdaptDefine(Test001, TestTarget, "__Test001") = {
    AdaptPassThrough(TestTarget::GetBasis),
    AdaptPassThrough(TestTarget::AddToBasis),
    AdaptPassThrough(TestTarget::SubFromBasis),
};

class ITest002 {
public:
    virtual int GetBasis()                   = 0;
    virtual int SubFrombasis(int n1, int n2) = 0;
};

} // namespace

bool TestTrampolines() {
    auto t1 = (TestTarget *)__Create_Test001_interface();

    t1->AddToBasis(5);
    t1->SubFromBasis(4, 8);

    return t1->GetBasis() == 3;
}

TEST_CASE("Trampolines work", "[trampoline]") {
    REQUIRE(TestTrampolines() == 1);
};
