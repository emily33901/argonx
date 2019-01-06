#include "types.hh"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <tuple>
#include <vector>

class Buffer {
    std::vector<u8> storage;
    size_t          offset = 0;
    size_t          base   = 0;

    template <typename T>
    static constexpr bool ValidToWrite = std::is_trivially_constructible_v<T> && !std::is_pointer_v<T>;

    decltype(storage.begin()) OffsetIterator() {
        return storage.begin() + base + offset;
    }

    void WriteData(const u8 *buffer, size_t count) {
        storage.insert(OffsetIterator(), buffer, buffer + count);
        offset += count;
    }

    u8 *ReadDataInPlace(size_t size) {
        auto i = &*OffsetIterator();
        offset += size;

        return i;
    }

public:
    Buffer() {
    }

    template <typename... Args>
    explicit Buffer(Args... args) {
        Write(std::forward<Args>(args)...);
    }

    void   Seek(i32 off) { offset += off; }
    size_t Tell() { return offset; }

    void SetPos(size_t pos) { offset = pos; }

    template <typename T>
    void SetBase() { base = sizeof(T); }
    void SetBase(u32 pos) { base = pos; }

    template <typename T>
    void SeekBase() { base += sizeof(T); }
    void SeekBase(i32 off) { base += off; }

    size_t                 SizeNoBase() { return storage.size() - base; }
    size_t                 Size() { return storage.size(); }
    const std::vector<u8> &Storage() { return storage; }

    template <typename T>
    std::enable_if_t<ValidToWrite<T>> Write(const T data) {
        const auto length = sizeof(T);

        auto dataInBytes = reinterpret_cast<const u8 *>(&data);

        WriteData(dataInBytes, length);
    }

    template <typename T, typename SizeT>
    std::enable_if_t<ValidToWrite<T>, void> Write(const std::pair<T *, SizeT> data) {
        auto [arr, length] = data;

        auto dataInBytes   = reinterpret_cast<const u8 *>(arr);
        auto lengthInBytes = length * sizeof(T);

        WriteData(dataInBytes, lengthInBytes);
    }

    template <typename T, size_t N>
    void Write(T (&x)[N]) {
        Write(std::make_pair(x, N));
    }

    void Write(const Buffer b) {
        return Write(b.storage);
    }

    void Write(const std::vector<u8> &b) {
        WriteData(b.data(), b.size());
    }

    template <typename... Args>
    std::enable_if_t<(sizeof...(Args) > 1)> Write(Args... args) {
        (Write(std::forward<Args>(args)), ...);
    }

    template <typename T>
    std::enable_if_t<ValidToWrite<T>, T> Read() {
        return *reinterpret_cast<T *>(ReadDataInPlace(sizeof(T)));
    }

    template <typename T>
    std::enable_if_t<ValidToWrite<T>, void> ReadInto(T &x) {
        x = Read<T>();
    }

    void ReadInto(std::vector<u8> &x) {
        assert(x.capacity() > 0); // If this goes off you havent reserved any space

        x.insert(x.end(), OffsetIterator(), OffsetIterator() + x.capacity());
    }

    template <typename... Args>
    std::enable_if_t<(sizeof...(Args) > 1)> Read(Args &... args) {
        (ReadInto(std::forward<Args &>(args)), ...);
    }
};
