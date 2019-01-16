#pragma once

#include "buffer.hh"

namespace Zip {
u8 *Deflate(u8 *in, size_t startingSize, size_t finalSize);
}