#include "precompiled.hh"

#include <catch2/catch.hpp>

#include "buffer.hh"
#include "platform.hh"

template <typename T>
auto WriteRead(T val) {
    Buffer b;
    b.Write(val);

    b.SetPos(0);

    return b.Read<T>();
}

int TestNewBuffer() {
    Buffer b;

    std::vector<u8> v{'B', 'A'};

    b.Write(13, 25, 15, 234, v);

    u32 a, c, d, e;

    std::vector<u8> v2;

    v2.reserve(13);

    b.SetPos(0);

    b.Read(a, c, d, e, v2);

    return b.Size();
}

TEST_CASE("Buffer", "[buffer]") {
    REQUIRE(TestNewBuffer() == 18);

    REQUIRE(WriteRead((u8)UINT8_MAX) == UINT8_MAX);
    REQUIRE(WriteRead((u16)UINT16_MAX) == UINT16_MAX);
    REQUIRE(WriteRead((u32)UINT32_MAX) == UINT32_MAX);
    REQUIRE(WriteRead((u64)UINT64_MAX) == UINT64_MAX);
};