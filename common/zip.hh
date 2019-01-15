#pragma once

#include "buffer.hh"

namespace Zip {
static u8 *Deflate(u8 *in, size_t startingSize, size_t finalSize);
}