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

// Turn a `CONST u8*,u32` into a pair for outParams
template <u32 idx, typename... Ts, typename... TRes, typename... TReal>
struct OutParamsHelper<idx, std::tuple<const u8 *, u32, Ts...>, std::tuple<TRes...>, std::tuple<TReal...>>
    : OutParamsHelper<(idx + 1), std::tuple<Ts...>, std::tuple<TRes...>, std::tuple<TReal..., IndexedParam<std::pair<const u8 *, u32>, idx>>> {};

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
    using Result     = typename OutParamsHelper<0, std::tuple<Ts...>>;
    using OutParams  = typename Result::OutParams;
    using RealParams = typename Result::RealParams;
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

    using OutParamsNonPointer = typename _OutParamsNonPointer<OutParams>::Type;

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

    using OutParamsStorage = typename _OutParamsStorage<OutParamsNonPointer>::Type;
    using RealArgsStorage  = typename _OutParamsStorage<RealArgs>::Type;
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

    template <typename T>
    struct _ReadHelper;

    template <typename T>
    struct _ReadHelper<std::tuple<T>> {
        using ThisT                  = typename T::Type;
        static constexpr int thisIdx = T::index;

        static void Read(Buffer &data, Args &args) {
            data.ReadInto(std::get<thisIdx>(args));
        }
    };

    template <typename T, typename... Ts>
    struct _ReadHelper<std::tuple<T, Ts...>> {
        using Base                   = _ReadHelper<std::tuple<Ts...>>;
        using ThisT                  = typename T::Type;
        static constexpr int thisIdx = T::index;

        static void Read(Buffer &data, Args &args) {
            data.ReadInto(std::get<thisIdx>(args));

            return Base::Read(data, args);
        }
    };

    static void ReadRealVariables(Buffer &data, Args &args) {
        if constexpr (!std::is_same_v<RealArgs, std::tuple<>>)
            _ReadHelper<RealArgs>::Read(data, args);
    }

    template <typename T>
    struct _SetOutVariablesHelper;

    template <typename T>
    struct _SetOutVariablesHelper<std::tuple<T>> {
        using ThisT                  = typename T::Type;
        static constexpr int thisIdx = T::index;

        static void Read(Buffer &data, Args &args) {
            if constexpr (Platform::is_pair_v<ThisT>)
                data.ReadInto(std::make_pair(std::get<thisIdx>(args), std::get<(thisIdx + 1)>(args)));
            else
                data.ReadInto(std::get<thisIdx>(args));
        }
    };

    template <typename T, typename... Ts>
    struct _SetOutVariablesHelper<std::tuple<T, Ts...>> {
        using Base                   = _SetOutVariablesHelper<std::tuple<Ts...>>;
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

    static void SetOutVariables(Buffer &data, Args &args) {
        if constexpr (!std::is_same_v<OutParams, std::tuple<>>)
            _SetOutVariablesHelper<OutParams>::Read(data, args);
    }

    template <typename T>
    struct _WriteRealHelper;

    template <typename T>
    struct _WriteRealHelper<std::tuple<T>> {
        using ThisT                  = typename T::Type;
        static constexpr int thisIdx = T::index;

        static void Write(Buffer &data, Args &args) {
            data.Write(std::get<thisIdx>(args));

            // Special exception for if it is a pair
            // We need to write the length afterwards
            if constexpr (Platform::is_pair_v<ThisT>)
                data.Write(std ::get<thisIdx>(args).second);
        }
    };

    template <typename T, typename... Ts>
    struct _WriteRealHelper<std::tuple<T, Ts...>> {
        using Base                   = _WriteRealHelper<std::tuple<Ts...>>;
        using ThisT                  = typename T::Type;
        static constexpr int thisIdx = T::index;

        static void Write(Buffer &data, Args &args) {
            data.Write(std::get<thisIdx>(args));

            // Special exception for if it is a pair
            // We need to write the length afterwards
            if constexpr (Platform::is_pair_v<ThisT>)
                data.Write(std ::get<thisIdx>(args).second);

            return Base::Write(data, args);
        }
    };

    static void WriteRealArgsToBuffer(Buffer &data, Args &args) {
        if constexpr (!std::is_same_v<RealArgs, std::tuple<>>)
            _WriteRealHelper<RealArgs>::Write(data, args);
    }

    template <u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut, typename TReal, typename TOut>
    struct _SpliceRead;

    template <u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut>
    struct _SpliceRead<thisIdx, thisIdxReal, thisIdxOut, std::tuple<>, std::tuple<>> {
        static void Read(Args &toBuild, RealArgsStorage &realStorage, OutParamsStorage &outStore) {}
    };

    template <u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut, typename TReal, typename... TReals, int idxReal>
    struct _SpliceRead<thisIdx, thisIdxReal, thisIdxOut, std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<>> {

        using BaseIfReal       = _SpliceRead<(thisIdx + 1), (thisIdxReal + 1), thisIdxOut, std::tuple<TReals...>, std::tuple<>>;
        using BaseIfRealIfPair = _SpliceRead<(thisIdx + 2), (thisIdxReal + 1), thisIdxOut, std::tuple<TReals...>, std::tuple<>>;
        // using BaseIfOut  = _SpliceRead<(thisIdx + 1), std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<>>;

        static void Read(Args &toBuild, RealArgsStorage &realStorage, OutParamsStorage &outStore) {
            if constexpr (thisIdx == idxReal) {
                std::get<thisIdx>(toBuild) = std::get<thisIdxReal>(realStorage);

                if constexpr (Platform::is_pair_v<TReal>)
                    BaseIfRealIfPair::Read(toBuild, realStorage, outStore);
                else
                    BaseIfReal::Read(toBuild, realStorage, outStore);
            } else {
                static_assert(0, "This should NEVER happen! Your two types do not line up correctly");
            }
        }
    };

    template <u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut, typename TOut, typename... TOuts, int idxOut>
    struct _SpliceRead<thisIdx, thisIdxReal, thisIdxOut, std::tuple<>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>> {

        // using BaseIfReal = _SpliceRead<(thisIdx + 1), std::tuple<>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>>;
        using BaseIfOut       = _SpliceRead<(thisIdx + 1), thisIdxReal, (thisIdxOut + 1), std::tuple<>, std::tuple<TOuts...>>;
        using BaseIfOutIfPair = _SpliceRead<(thisIdx + 2), thisIdxReal, (thisIdxOut + 1), std::tuple<>, std::tuple<TOuts...>>;

        static void Read(Args &toBuild, RealArgsStorage &realStorage, OutParamsStorage &outStore) {
            if constexpr (thisIdx == idxOut) {
                if constexpr (Platform::is_pair_v<TOut>) {
                    auto &[ptr, len] = std::get<thisIdxOut>(outStore);

                    // TODO: WE NEED TO FREE THIS MEMORY SOMEWHERE!!!!
                    ptr = (u8 *)malloc(len);

                    std::get<thisIdx>(toBuild)       = ptr;
                    std::get<(thisIdx + 1)>(toBuild) = len;

                    BaseIfOutIfPair::Read(toBuild, realStorage, outStore);
                } else {
                    std::get<thisIdx>(toBuild) = &std::get<thisIdxOut>(outStore);

                    BaseIfOut::Read(toBuild, realStorage, outStore);
                }
            } else {
                static_assert(0, "This should NEVER happen! Your two types do not line up correctly");
            }
        }
    };

    template <u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut, typename TReal, typename TOut, typename... TOuts, int idxReal, int idxOut>
    struct _SpliceRead<thisIdx, thisIdxReal, thisIdxOut, std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>> {

        using BaseIfReal       = _SpliceRead<(thisIdx + 1), (thisIdxReal + 1), thisIdxOut, std::tuple<>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>>;
        using BaseIfRealIfPair = _SpliceRead<(thisIdx + 2), (thisIdxReal + 1), thisIdxOut, std::tuple<>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>>;

        using BaseIfOut       = _SpliceRead<(thisIdx + 1), thisIdxReal, (thisIdxOut + 1), std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>>, std::tuple<TOuts...>>;
        using BaseIfOutIfPair = _SpliceRead<(thisIdx + 2), thisIdxReal, (thisIdxOut + 1), std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>>, std::tuple<TOuts...>>;

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

                    // TODO: WE NEED TO FREE THIS MEMORY SOMEWHERE!!!!
                    ptr = (u8 *)malloc(len);

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

    template <u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut, typename TReal, typename... TReals, typename TOut, int idxReal, int idxOut>
    struct _SpliceRead<thisIdx, thisIdxReal, thisIdxOut, std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>>> {

        using BaseIfReal       = _SpliceRead<(thisIdx + 1), (thisIdxReal + 1), thisIdxOut, std::tuple<TReals...>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>>>;
        using BaseIfRealIfPair = _SpliceRead<(thisIdx + 2), (thisIdxReal + 1), thisIdxOut, std::tuple<TReals...>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>>>;

        using BaseIfOut       = _SpliceRead<(thisIdx + 1), thisIdxReal, (thisIdxOut + 1), std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<>>;
        using BaseIfOutIfPair = _SpliceRead<(thisIdx + 2), thisIdxReal, (thisIdxOut + 1), std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<>>;

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

                    // TODO: WE NEED TO FREE THIS MEMORY SOMEWHERE!!!!
                    ptr = (u8 *)malloc(len);

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

    template <u32 thisIdx, u32 thisIdxReal, u32 thisIdxOut, typename TReal, typename TOut, typename... TReals, typename... TOuts, int idxReal, int idxOut>
    struct _SpliceRead<thisIdx, thisIdxReal, thisIdxOut, std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>> {

        using BaseIfReal       = _SpliceRead<(thisIdx + 1), (thisIdxReal + 1), thisIdxOut, std::tuple<TReals...>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>>;
        using BaseIfRealIfPair = _SpliceRead<(thisIdx + 2), (thisIdxReal + 1), thisIdxOut, std::tuple<TReals...>, std::tuple<RpcHelpers::IndexedParam<TOut, idxOut>, TOuts...>>;

        using BaseIfOut       = _SpliceRead<(thisIdx + 1), thisIdxReal, (thisIdxOut + 1), std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<TOuts...>>;
        using BaseIfOutIfPair = _SpliceRead<(thisIdx + 2), thisIdxReal, (thisIdxOut + 1), std::tuple<RpcHelpers::IndexedParam<TReal, idxReal>, TReals...>, std::tuple<TOuts...>>;

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

                    // TODO: WE NEED TO FREE THIS MEMORY SOMEWHERE!!!!
                    ptr = (u8 *)malloc(len);

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

    static void BuildArgs(Args &toBuild, RealArgsStorage &realStorage, OutParamsStorage &outStore) {
        // TODO: we probably need some better detection of
        // empty realStorage / empty outStore

        if constexpr (!std::is_same_v<Args, std::tuple<>>)
            _SpliceRead<0, 0, 0, RealArgs, OutParams>::Read(toBuild, realStorage, outStore);
    }

    template <u32 idx, typename T>
    struct _ReadBufferSize;

    template <u32 idx, typename T>
    struct _ReadBufferSize<idx, std::tuple<T>> {
        static void Read(Buffer &b, Args &args) {}
    };

    template <u32 idx, typename T, typename T1>
    struct _ReadBufferSize<idx, std::tuple<T, T1>> {
        static void Read(Buffer &b, Args &args) {
            if constexpr (std::is_same_v<std::pair<T, T1>, std::pair<u8 *, u32>>)
                b.ReadInto(std::get<(idx + 1)>(args));
        }
    };

    template <u32 idx, typename T, typename T1, typename... Ts>
    struct _ReadBufferSize<idx, std::tuple<T, T1, Ts...>> {
        using Base = _ReadBufferSize<(idx + 1), std::tuple<T1, Ts...>>;

        static void Read(Buffer &b, Args &args) {
            if constexpr (std::is_same_v<std::pair<T, T1>, std::pair<u8 *, u32>>)
                b.ReadInto(std::get<(idx + 1)>(args));

            Base::Read(b, args);
        }
    };

    template <u32 idx, typename T>
    struct _WriteBufferSizeToStorage;

    template <u32 idx, typename T>
    struct _WriteBufferSizeToStorage<idx, std::tuple<T>> {
        using ThisT                  = typename T::Type;
        static constexpr int thisIdx = T::index;

        static void Write(Args &args, OutParamsStorage &storage) {
            if constexpr (Platform::is_pair_v<ThisT>)
                std::get<idx>(storage).second = std::get<(thisIdx + 1)>(args);
        }
    };

    template <u32 idx, typename T, typename... Ts>
    struct _WriteBufferSizeToStorage<idx, std::tuple<T, Ts...>> {
        using Base                   = _WriteBufferSizeToStorage<(idx + 1), std::tuple<Ts...>>;
        using ThisT                  = typename T::Type;
        static constexpr int thisIdx = T::index;

        static void Write(Args &args, OutParamsStorage &storage) {
            if constexpr (Platform::is_pair_v<ThisT>)
                std::get<idx>(storage).second = std::get<(thisIdx + 1)>(args);

            return Base::Write(args, storage);
        }
    };

    static void ReadBufferSizes(Buffer &b, Args &args, OutParamsStorage &storage) {
        if constexpr (!std::is_same_v<Args, std::tuple<>>) {
            _ReadBufferSize<0, Args>::Read(b, args);

            if constexpr (!std::is_same_v<OutParamsStorage, std::tuple<>>)
                _WriteBufferSizeToStorage<0, OutParams>::Write(args, storage);
        }
    }

    template <u32 idx, typename T>
    struct _WriteBufferSize;

    template <u32 idx, typename T>
    struct _WriteBufferSize<idx, std::tuple<T>> {
        static void Write(Buffer &b, Args &args) {}
    };

    template <u32 idx, typename T, typename T1>
    struct _WriteBufferSize<idx, std::tuple<T, T1>> {
        static void Write(Buffer &b, Args &args) {
            if constexpr (std::is_same_v<std::pair<T, T1>, std::pair<u8 *, u32>>)
                b.Write(std::get<(idx + 1)>(args));
        }
    };

    template <u32 idx, typename T, typename T1, typename... Ts>
    struct _WriteBufferSize<idx, std::tuple<T, T1, Ts...>> {
        using Base = _WriteBufferSize<(idx + 1), std::tuple<T1, Ts...>>;

        static void Write(Buffer &b, Args &args) {
            if constexpr (std::is_same_v<std::pair<T, T1>, std::pair<u8 *, u32>>)
                b.Write(std::get<(idx + 1)>(args).second);

            Base::Write(b, args);
        }
    };

    static void WriteBufferSizes(Buffer &b, Args &args) {
        if constexpr (!std::is_same_v<Args, std::tuple<>>)
            _WriteBufferSize<0, Args>::Write(b, args);
    }
};

} // namespace RpcHelpers
} // namespace Steam