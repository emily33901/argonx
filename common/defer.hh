#pragma once

// helper class / macro for creating scope exit actions

template <class Lambda>
class AtScopeExit {
    Lambda &l;

public:
    AtScopeExit(Lambda &action) : l(action) {}
    ~AtScopeExit() { l(); }
};

#define Defer_INTERNAL2(lname, aname, ...)                       \
    auto                         lname = [&]() { __VA_ARGS__; }; \
    AtScopeExit<decltype(lname)> aname(lname);

#define Defer_TOKENPASTE(x, y) Defer_##x##y

#define Defer_INTERNAL1(ctr, ...)                 \
    Defer_INTERNAL2(Defer_TOKENPASTE(func_, ctr), \
                    Defer_TOKENPASTE(instance_, ctr), __VA_ARGS__)

#define Defer(...) Defer_INTERNAL1(__COUNTER__, __VA_ARGS__)

// helper class for running a function at init time
template <class Lambda>
class AtInitTime {
public:
    AtInitTime(Lambda &action) { action(); };
};

#define AtInit_INTERNAL2(lname, aname, ...)                    \
    auto                        lname = []() { __VA_ARGS__; }; \
    AtInitTime<decltype(lname)> aname(lname);

#define AtInit_TOKENPASTE(x, y) AtInit_##x##y

#define AtInit_INTERNAL1(ctr, ...)                  \
    AtInit_INTERNAL2(AtInit_TOKENPASTE(func_, ctr), \
                     AtInit_TOKENPASTE(instance_, ctr), __VA_ARGS__)

#define InitTime(...) AtInit_INTERNAL1(__COUNTER__, __VA_ARGS__);