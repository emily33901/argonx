#include "types.hh"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <tuple>
#include <vector>

class Buffer {
    std::vector<u8> storage;
    size_t          readOffset = 0;

    // returns original end of buffer
    auto GrowBuffer(int additional) {
        const auto currentSize = storage.size();

        storage.resize(currentSize + additional);
        return storage.end() - additional;
    }

    template <typename T>
    static constexpr bool ValidToWrite = std::is_trivially_constructible_v<T> && !std::is_pointer_v<T>;

    template <typename T>
    struct IsArray : std::false_type {};

public:
    Buffer() {}

    template <typename T>
    std::enable_if_t<!ValidToWrite<T> && !std::is_pointer_v<T>> Write(T) {
        // static_assert(0, "Write not implmented for T");
        assert(false);
    }

    template <typename T>
    std::enable_if_t<std::is_pointer_v<T>> Write(T) {
        // static_assert(0, "Write not implemented for pointers (did you mean an array: use std::make_pair(pointer, length);");
        assert(false);
    }

    template <typename T>
    std::enable_if_t<ValidToWrite<T>> Write(const T data) {
        const auto length = sizeof(T);

        auto dataInBytes = reinterpret_cast<const u8 *>(&data);

        std::copy(dataInBytes, dataInBytes + length, GrowBuffer(length));
    }

    template <typename T>
    std::enable_if_t<ValidToWrite<T>> Write(const std::pair<T *, size_t> data) {
        auto [arr, length] = data;

        auto dataInBytes   = reinterpret_cast<const u8 *>(arr);
        auto lengthInBytes = length * sizeof(T);

        // Write<u16>(length);

        std::copy(dataInBytes, dataInBytes + lengthInBytes, GrowBuffer(lengthInBytes));
    }

    void Write(const std::pair<std::string, bool> data) {
        auto [str, nullable] = data;

        bool empty = str.empty();

        if (empty && nullable) {
            Write<u8>(0);
        } else if (empty) {
            Write<u8, u8>(11, 0);
        } else {
            Write<u8>(11);

            // write raw data by leb128 something
            Write(std::make_pair(str.c_str(), str.length()));
        }
    }

    template <typename T, size_t N>
    void Write(T (&x)[N]) {
        Write(std::make_pair(x, N));
    }

    void Write(const std::string s) {
        return Write(std::make_pair(s, true));
    }

    void Write(const Buffer b) {
        return Write(b.storage);
    }

    void Write(const std::vector<u8> &b) {
        for (auto v : b) {
            Write(v);
        }
    }

    template <typename... Types>
    void Write(std::tuple<Types...> &&t) {
        std::apply([this](auto &&... x) { (Write(std::forward<decltype(x)>(x)), ...); }, std::forward<std::tuple<Types...>>(t));
    }

    template <typename... Args>
    std::enable_if_t<(sizeof...(Args) > 1)> Write(Args... args) {
        Write(std::forward_as_tuple(args...));
    }

    template <typename... Args>
    Buffer(Args... args) {
        Write(std::forward<Args>(args)...);
    }

    template <typename T>
    void RewindRead() {
        // TODO: do the enable_if checks for ValidToWrite...
        readOffset -= sizeof(T);
    }

    void SeekRead(u32 offset) {
        readOffset = offset;
    }

    template <typename T>
    std::enable_if_t<!ValidToWrite<T> && !std::is_pointer_v<T>, T> Read() {
        // static_assert(0, "read not implmented for T");
        assert(false);
    }

    template <typename T>
    std::enable_if_t<ValidToWrite<T>, T> Read() {
        const auto length = sizeof(T);
        T          d      = *reinterpret_cast<T *>(storage.data() + readOffset);

        readOffset += length;

        return d;
    }

#if 0
        
    template <typename T>
    std::pair<std::enable_if_t<std::is_pointer_v<T> && ValidToWrite<std::remove_pointer_t<T>>, T>, size_t> Read() {
        const auto length = Read<u16>();

        auto r = std::make_pair(reinterpret_cast<T>(storage.data() + readOffset), length);

        readOffset += length;

        return r;
    }



    std::string Read() {
        auto nulled = Read<u8>();

        if (nulled != 11) return "";

        // do the leb128
        auto [str, length] = Read<char *>();
        return std::string(str, length);
    }
#endif

    template <typename T>
    void ReadInto(T &x) {
        constexpr auto extents = std::extent_v<std::remove_reference_t<T>>;

        if constexpr (extents > 0 || std::is_pointer_v<T>) {
            auto [ptr, size] = Read<std::decay_t<T>>();
            std::memcpy(x, ptr, size * sizeof(std::remove_extent_t<T>));
        } else {
            x = Read<std::remove_reference_t<T>>();
        }
    }

    template <typename T, size_t N>
    void ReadInto(T (&x)[N]) {
        auto [ptr, size] = Read<T *>();

        // assert(size == N);

        std::memcpy(x, ptr, size);
    }

    template <typename... Types>
    void Read(std::tuple<Types...> &&t) {
        std::apply([this](auto &&... x) {
            (ReadInto<decltype(x)>(x), ...);
        },
                   std::forward<std::tuple<Types...>>(t));
    }

    template <typename... Args>
    std::enable_if_t<(sizeof...(Args) > 1)> Read(Args &... args) {
        Read(std::forward_as_tuple(args...));
    }

    u32 Size() {
        return storage.size();
    }

    const std::vector<u8> &Body() {
        return storage;
    }
};
