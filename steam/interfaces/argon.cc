#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

// Not techincally a 'Steam' interface however...

template <bool isServer>
class Argon {
public:
};

AdaptExposeClientServerNoUser(Argon, "Argon");
