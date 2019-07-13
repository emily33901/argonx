#pragma once

#include <type_traits>
#include <utility>

#include "platform.hh"

// Welcome to hell
// These are templates that do the devils bidding

// Notably:
// - Seperating a function pointers return class and args
// - Constructing several other types based of these
// - Seperating "real" arguments from "out" arguments
// - Indexing those
// - Reading and writing buffer lengths for some "outs"
// - Reading and writing some "out" variables

namespace Steam {
namespace RpcHelpers {
// Store the index with the type
template <typename T, int idx>
struct IndexedParam {
    using Type                 = T;
    static constexpr int index = idx;
};

template <u32 idx, typename Tuple, typename Res = std::tuple<>, typename RealRes = std::tuple<>>
struct OutParamsHelper;

// Result
template <u32 idx, typename Res, typename RealRes>
struct OutParamsHelper<idx, std::tuple<>, Res, RealRes> {
    using OutParams  = Res;
    using RealParams = RealRes;
};

// Turn a `u8*,u32` into a pair for outParams
template <u32 idx, typename... Ts, typename... TRes, typename... TReal>
struct OutParamsHelper<idx, std::tuple<u8 *, u32, Ts...>, std::tuple<TRes...>, std::tuple<TReal...>>
    : OutParamsHelper<(idx + 1), std::tuple<Ts...>, std::tuple<TRes..., IndexedParam<std::pair<u8 *, u32>, idx>>, std::tuple<TReal...>> {};

// Remove const char *
template <u32 idx, typename... Ts, typename... TRes, typename... TReal>
struct OutParamsHelper<idx, std::tuple<const char *, Ts...>, std::tuple<TRes...>, std::tuple<TReal...>>
    : OutParamsHelper<(idx + 1), std::tuple<Ts...>, std::tuple<TRes...>, std::tuple<TReal..., IndexedParam<const char *, idx>>> {};

// Include any T*
template <u32 idx, typename T, typename... Ts, typename... TRes, typename... TReal>
struct OutParamsHelper<idx, std::tuple<T *, Ts...>, std::tuple<TRes...>, std::tuple<TReal...>>
    : OutParamsHelper<(idx + 1), std::tuple<Ts...>, std::tuple<TRes..., IndexedParam<T *, idx>>, std::tuple<TReal...>> {};

// Remove any T
template <u32 idx, typename T, typename... Ts, typename... TRes, typename... TReal>
struct OutParamsHelper<idx, std::tuple<T, Ts...>, std::tuple<TRes...>, std::tuple<TReal...>>
    : OutParamsHelper<(idx + 1), std::tuple<Ts...>, std::tuple<TRes...>, std::tuple<TReal..., IndexedParam<T, idx>>> {};

template <typename... Ts>
struct _OutParams {
    using Result     = OutParamsHelper<0, std::tuple<Ts...>>;
    using OutParams  = typename Result::OutParams;
    using RealParams = typename Result::RealParams;
};

template <typename T>
struct _OutParamsNonPointer;

template <>
struct _OutParamsNonPointer<std::tuple<>> {
    using Type = std::tuple<>;
};

template <typename... T, int... idx>
struct _OutParamsNonPointer<std::tuple<IndexedParam<T, idx>...>> {
    using Type = std::tuple<IndexedParam<std::remove_pointer_t<T>, idx>...>;
};

template <typename T>
struct _OutParamsStorage;

template <>
struct _OutParamsStorage<std::tuple<>> {
    using Type = std::tuple<>;
};

template <typename... T, int... idx>
struct _OutParamsStorage<std::tuple<IndexedParam<T, idx>...>> {
    using Type = std::tuple<T...>;
};

template <typename F>
struct GetRpcImpl;

template <typename R, typename C, typename... A>
struct GetRpcImpl<R (C::*)(A...)> {
    using Ret   = R;
    using Class = C;
    using Args  = std::tuple<Platform::remove_cvref_t<A>...>;

    using OutParamsResult = _OutParams<A...>;

    using RealArgs  = typename OutParamsResult::RealParams;
    using OutParams = typename OutParamsResult::OutParams;

    using VirtualType = Ret(PlatformThisCall *)(void *instance, PlatformEdx A...);

    using OutParamsNonPointer = typename _OutParamsNonPointer<OutParams>::Type;

    using OutParamsStorage = typename _OutParamsStorage<OutParamsNonPointer>::Type;
    using RealArgsStorage  = typename _OutParamsStorage<RealArgs>::Type;
};

template <typename Args, typename T>
struct _ReadHelper;

template <typename Args>
struct _ReadHelper<Args, std::tuple<>> {
    static void Read(Buffer &data, Args &args) {}
};

template <typename Args, typename T, typename... Ts>
struct _ReadHelper<Args, std::tuple<T, Ts...>> {
    using Base                   = _ReadHelper<Args, std::tuple<Ts...>>;
    using ThisT                  = typename T::Type;
    static constexpr int thisIdx = T::index;

    static void Read(Buffer &data, Args &args) {
        data.ReadInto(std::get<thisIdx>(args));

        return Base::Read(data, args);
    }
};

template <typename Args, typename T>
struct _SetOutVariablesHelper;

template <typename Args>
struct _SetOutVariablesHelper<Args, std::tuple<>> {
    static void Read(Buffer &data, Args &args) {}
};

template <typename Args, typename T, typename... Ts>
struct _SetOutVariablesHelper<Args, std::tuple<T, Ts...>> {
    using Base                   = _SetOutVariablesHelper<Args, std::tuple<Ts...>>;
    using ThisT                  = typename T::Type;
    static constexpr int thisIdx = T::index;

    static void Read(Buffer &data, Args &args) {
        if constexpr (Platform::is_pair_v<ThisT>)
            data.ReadInto(std::make_pair(std::get<thisIdx>(args), std::get<(thisIdx + 1)>(args)));
        else
            data.ReadInto(std::get<thisIdx>(args));

        return Base::Read(data, args);
    }
};

template <typename Args, typename T>
struct _WriteRealHelper;

template <typename Args>
struct _WriteRealHelper<Args, std::tuple<>> {
    static void Write(Buffer &data, Args &args) {}
};

template <typename Args, typename T, typename... Ts>
struct _WriteRealHelper<Args, std::tuple<T, Ts...>> {
    using Base                   = _WriteRealHelper<Args, std::tuple<Ts...>>;
    using ThisT                  = typename T::Type;
    static constexpr int thisIdx = T::index;

    static void Write(Buffer &data, Args &args) {
        data.Write(std::get<thisIdx>(args));

        return Base::Write(data, args);
    }
};

template <typename Args, typename T>
struct _WriteOutHelper;

template <typename Args>
struct _WriteOutHelper<Args, std::tuple<>> {
    static void Write(Buffer &data, Args &args) {}
};

template <typename Args, typename T, typename... Ts>
struct _WriteOutHelper<Args, std::tuple<T, Ts...>> {
    using Base                   = _WriteOutHelper<Args, std::tuple<Ts...>>;
    using ThisT                  = typename T::Type;
    static constexpr int thisIdx = T::index;

    static void Write(Buffer &data, Args &args) {
        data.Write(*std::get<thisIdx>(args));

        return Base::Write(data, args);
    }
};

template <typename Args, typename RealArgsStorage, typename OutParamsStorage, u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut, typename TReal, typename TOut>
struct _SpliceRead;

template <typename Args, typename RealArgsStorage, typename OutParamsStorage, u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut>
struct _SpliceRead<Args, RealArgsStorage, OutParamsStorage, thisIdx, thisIdxReal, thisIdxOut, std::tuple<>, std::tuple<>> {
    static void Read(Args &toBuild, RealArgsStorage &realStorage, OutParamsStorage &outStore) {}
};

template <typename Args, typename RealArgsStorage, typename OutParamsStorage, u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut, typename TReal, typename... TReals, int idxReal>
struct _SpliceRead<Args, RealArgsStorage, OutParamsStorage, thisIdx, thisIdxReal, thisIdxOut, std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<>> {

    using BaseIfReal       = _SpliceRead<Args, RealArgsStorage, OutParamsStorage, (thisIdx + 1), (thisIdxReal + 1), thisIdxOut, std::tuple<TReals...>, std::tuple<>>;
    using BaseIfRealIfPair = _SpliceRead<Args, RealArgsStorage, OutParamsStorage, (thisIdx + 2), (thisIdxReal + 1), thisIdxOut, std::tuple<TReals...>, std::tuple<>>;
    // using BaseIfOut  = _SpliceRead<(thisIdx + 1), std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<>>;

    static void Read(Args &toBuild, RealArgsStorage &realStorage, OutParamsStorage &outStore) {
        if constexpr (thisIdx == idxReal) {
            std::get<thisIdx>(toBuild) = std::get<thisIdxReal>(realStorage);

            if constexpr (Platform::is_pair_v<TReal>)
                BaseIfRealIfPair::Read(toBuild, realStorage, outStore);
            else
                BaseIfReal::Read(toBuild, realStorage, outStore);
        } else {
            Assert(0, "This should NEVER happen! Your two types do not line up correctly");
        }
    }
};

template <typename Args, typename RealArgsStorage, typename OutParamsStorage, u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut, typename TOut, typename... TOuts, int idxOut>
struct _SpliceRead<Args, RealArgsStorage, OutParamsStorage, thisIdx, thisIdxReal, thisIdxOut, std::tuple<>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>> {

    // using BaseIfReal = _SpliceRead<(thisIdx + 1), std::tuple<>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>>;
    using BaseIfOut       = _SpliceRead<Args, RealArgsStorage, OutParamsStorage, (thisIdx + 1), thisIdxReal, (thisIdxOut + 1), std::tuple<>, std::tuple<TOuts...>>;
    using BaseIfOutIfPair = _SpliceRead<Args, RealArgsStorage, OutParamsStorage, (thisIdx + 2), thisIdxReal, (thisIdxOut + 1), std::tuple<>, std::tuple<TOuts...>>;

    static void Read(Args &toBuild, RealArgsStorage &realStorage, OutParamsStorage &outStore) {
        if constexpr (thisIdx == idxOut) {
            if constexpr (Platform::is_pair_v<TOut>) {
                auto &[ptr, len] = std::get<thisIdxOut>(outStore);

                std::get<thisIdx>(toBuild)       = ptr;
                std::get<(thisIdx + 1)>(toBuild) = len;

                BaseIfOutIfPair::Read(toBuild, realStorage, outStore);
            } else {
                std::get<thisIdx>(toBuild) = &std::get<thisIdxOut>(outStore);

                BaseIfOut::Read(toBuild, realStorage, outStore);
            }
        } else {
            Assert(0, "This should NEVER happen! Your two types do not line up correctly");
        }
    }
};

template <typename Args, typename RealArgsStorage, typename OutParamsStorage, u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut, typename TReal, typename TOut, typename... TReals, typename... TOuts, int idxReal, int idxOut>
struct _SpliceRead<Args, RealArgsStorage, OutParamsStorage, thisIdx, thisIdxReal, thisIdxOut, std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>> {

    using BaseIfReal       = _SpliceRead<Args, RealArgsStorage, OutParamsStorage, (thisIdx + 1), (thisIdxReal + 1), thisIdxOut, std::tuple<TReals...>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>>;
    using BaseIfRealIfPair = _SpliceRead<Args, RealArgsStorage, OutParamsStorage, (thisIdx + 2), (thisIdxReal + 1), thisIdxOut, std::tuple<TReals...>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>>;

    using BaseIfOut       = _SpliceRead<Args, RealArgsStorage, OutParamsStorage, (thisIdx + 1), thisIdxReal, (thisIdxOut + 1), std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<TOuts...>>;
    using BaseIfOutIfPair = _SpliceRead<Args, RealArgsStorage, OutParamsStorage, (thisIdx + 2), thisIdxReal, (thisIdxOut + 1), std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<TOuts...>>;

    static void Read(Args &toBuild, RealArgsStorage &realStorage, OutParamsStorage &outStore) {
        if constexpr (thisIdx == idxReal) {
            std::get<thisIdx>(toBuild) = std::get<thisIdxReal>(realStorage);

            if constexpr (Platform::is_pair_v<TReal>)
                BaseIfRealIfPair::Read(toBuild, realStorage, outStore);
            else
                BaseIfReal::Read(toBuild, realStorage, outStore);
        } else if constexpr (thisIdx == idxOut) {
            if constexpr (Platform::is_pair_v<TOut>) {
                auto &[ptr, len] = std::get<thisIdxOut>(outStore);

                std::get<thisIdx>(toBuild)       = ptr;
                std::get<(thisIdx + 1)>(toBuild) = len;

                BaseIfOutIfPair::Read(toBuild, realStorage, outStore);
            } else {
                std::get<thisIdx>(toBuild) = &std::get<thisIdxOut>(outStore);

                BaseIfOut::Read(toBuild, realStorage, outStore);
            }
        }
    }
};

template <typename Args, u32 idx, typename T>
struct _ReadBuffers;

template <typename Args, u32 idx, typename T>
struct _ReadBuffers<Args, idx, std::tuple<T>> {
    static void Read(Buffer &b, Args &args) {}
};

template <typename Args, u32 idx, typename T, typename T1>
struct _ReadBuffers<Args, idx, std::tuple<T, T1>> {
    static void Read(Buffer &b, Args &args) {
        if constexpr (std::is_same_v<std::pair<T, T1>, std::pair<u8 *, u32>>) {
            b.ReadInto(std::get<(idx + 1)>(args));

            auto &ptr  = std::get<idx>(args);
            auto &size = std::get<(idx + 1)>(args);
            ptr        = (u8 *)malloc(size);

            b.ReadInto(std::make_pair(ptr, size));
        }
    }
};

template <typename Args, u32 idx, typename T, typename T1, typename... Ts>
struct _ReadBuffers<Args, idx, std::tuple<T, T1, Ts...>> {
    using Base = _ReadBuffers<Args, (idx + 1), std::tuple<T1, Ts...>>;

    static void Read(Buffer &b, Args &args) {
        if constexpr (std::is_same_v<std::pair<T, T1>, std::pair<u8 *, u32>>) {
            b.ReadInto(std::get<(idx + 1)>(args));

            auto &ptr  = std::get<idx>(args);
            auto &size = std::get<(idx + 1)>(args);
            ptr        = malloc(size);

            b.ReadInto(std::make_pair(ptr, size));
        }

        Base::Read(b, args);
    }
};

template <typename Args, typename OutParamsStorage, u32 idx, typename T>
struct _WriteBufferSizeToStorage;

template <typename Args, typename OutParamsStorage, u32 idx>
struct _WriteBufferSizeToStorage<Args, OutParamsStorage, idx, std::tuple<>> {
    static void Write(Args &args, OutParamsStorage &storage) {}
};

template <typename Args, typename OutParamsStorage, u32 idx, typename T, typename... Ts>
struct _WriteBufferSizeToStorage<Args, OutParamsStorage, idx, std::tuple<T, Ts...>> {
    using Base                   = _WriteBufferSizeToStorage<Args, OutParamsStorage, (idx + 1), std::tuple<Ts...>>;
    using ThisT                  = typename T::Type;
    static constexpr int thisIdx = T::index;

    static void Write(Args &args, OutParamsStorage &storage) {
        if constexpr (Platform::is_pair_v<ThisT>) {
            std::get<idx>(storage) = std::make_pair(std ::get<thisIdx>(args), std::get<(thisIdx + 1)>(args));
        }

        return Base::Write(args, storage);
    }
};

template <typename Args, u32 idx, typename T>
struct _WriteBuffers;

template <typename Args, u32 idx, typename T>
struct _WriteBuffers<Args, idx, std::tuple<T>> {
    static void Write(Buffer &b, Args &args) {}
};

template <typename Args, u32 idx, typename T, typename T1>
struct _WriteBuffers<Args, idx, std::tuple<T, T1>> {
    static void Write(Buffer &b, Args &args) {
        if constexpr (std::is_same_v<std::pair<T, T1>, std::pair<u8 *, u32>>) {
            b.Write(std::get<(idx + 1)>(args));

            b.Write(std::make_pair(std::get<idx>(args), std::get<(idx + 1)>(args)));
        }
    }
};

template <typename Args, u32 idx, typename T, typename T1, typename... Ts>
struct _WriteBuffers<Args, idx, std::tuple<T, T1, Ts...>> {
    using Base = _WriteBuffers<Args, (idx + 1), std::tuple<T1, Ts...>>;

    static void Write(Buffer &b, Args &args) {
        if constexpr (std::is_same_v<std::pair<T, T1>, std::pair<u8 *, u32>>) {
            b.Write(std::get<(idx + 1)>(args).second);

            b.Write(std::make_pair(std::get<idx>(args), std::get<(idx + 1)>(args)));
        }

        Base::Write(b, args);
    }
};

template <typename Args, typename T>
struct _FreeBuffers;

template <typename Args>
struct _FreeBuffers<Args, std::tuple<>> {
    static void Free(Args &args) {}
};

template <typename Args, typename T, typename... Ts>
struct _FreeBuffers<Args, std::tuple<T, Ts...>> {
    using Base                   = _FreeBuffers<Args, std::tuple<Ts...>>;
    using ThisT                  = typename T::Type;
    static constexpr int thisIdx = T::index;

    static void Free(Args &args) {
        if constexpr (Platform::is_pair_v<ThisT>)
            free(std::get<thisIdx>(args));

        return Base::Free(args);
    }
};

template <typename F>
struct RpcInternalDetail {
    using Types               = GetRpcImpl<F>;
    using Return              = typename Types::Ret;
    using Args                = typename Types::Args;
    using RealArgs            = typename Types::RealArgs;
    using RealArgsStorage     = typename Types::RealArgsStorage;
    using Class               = typename Types::Class;
    using VirtualType         = typename Types::VirtualType;
    using OutParams           = typename Types::OutParams;
    using OutParamsNonPointer = typename Types::OutParamsNonPointer;
    using OutParamsStorage    = typename Types::OutParamsStorage;

    static void ReadRealVariables(Buffer &data, Args &args) {
        if constexpr (!std::is_same_v<RealArgs, std::tuple<>>)
            _ReadHelper<Args, RealArgs>::Read(data, args);
    }

    static void SetOutVariables(Buffer &data, Args &args) {
        if constexpr (!std::is_same_v<OutParams, std::tuple<>>)
            _SetOutVariablesHelper<Args, OutParams>::Read(data, args);
    }

    static void WriteRealArgsToBuffer(Buffer &data, Args &args) {
        if constexpr (!std::is_same_v<RealArgs, std::tuple<>>)
            _WriteRealHelper<Args, RealArgs>::Write(data, args);
    }

    static void WriteOutParams(Buffer &data, Args &args) {
        if constexpr (!std::is_same_v<OutParams, std::tuple<>>)
            _WriteOutHelper<Args, OutParams>::Write(data, args);
    }

    static void BuildArgs(Args &toBuild, RealArgsStorage &realStorage, OutParamsStorage &outStore) {
        // TODO: we probably need some better detection of
        // empty realStorage / empty outStore

        if constexpr (!std::is_same_v<Args, std::tuple<>>)
            _SpliceRead<Args, RealArgsStorage, OutParamsStorage, 0, 0, 0, RealArgs, OutParams>::Read(toBuild, realStorage, outStore);
    }

    static void ReadBuffers(Buffer &b, Args &args, OutParamsStorage &storage) {
        if constexpr (!std::is_same_v<Args, std::tuple<>>) {
            _ReadBuffers<Args, 0, Args>::Read(b, args);

            if constexpr (!std::is_same_v<OutParamsStorage, std::tuple<>>)
                _WriteBufferSizeToStorage<Args, OutParamsStorage, 0, OutParams>::Write(args, storage);
        }
    }

    static void WriteBuffers(Buffer &b, Args &args) {
        if constexpr (!std::is_same_v<Args, std::tuple<>>)
            _WriteBuffers<Args, 0, Args>::Write(b, args);
    }

    static void FreeBuffers(Args &args) {
        _FreeBuffers<Args, OutParams>::Free(args);
    }
};

} // namespace RpcHelpers
} // namespace Steam