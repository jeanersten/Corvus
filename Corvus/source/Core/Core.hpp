#pragma once

#include <cstdint>

using Int8  = std::int8_t;
using Int16 = std::int16_t;
using Int32 = std::int32_t;
using Int64 = std::int64_t;

using Uint8  = std::uint8_t;
using Uint16 = std::uint16_t;
using Uint32 = std::uint32_t;
using Uint64 = std::uint64_t;

// api flags, usually shared library purpose
#if defined(CORVUS_PLATFORM_WIN32)
  #if defined(CORVUS_BUILD_ENGINE)
    #define CORVUS_API __declspec(dllexport)
  #else
    #define CORVUS_API __declspec(dllimport)
  #endif
#else
  #define CORVUS_API
#endif

// just shift 1 by N
#define CORVUS_BIT_MASK(N) ((Uint32)1 << N)
