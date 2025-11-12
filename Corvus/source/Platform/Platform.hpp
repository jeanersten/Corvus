#pragma once

#include "../Core/Core.hpp"
#include "D3D11Context.hpp"
#include "OpenGLContext.hpp"
#include "Win32EventPoll.hpp"
#include "Win32Window.hpp"

namespace Corvus
{
  class CORVUS_API Platform
  {
  public:
    template<typename T>
    static inline const T* GetDataPointer(Uint32 index)
    {
      return reinterpret_cast<const T*>(s_platform_data[index]);
    }

    static inline void SetDataPointer(Uint32 index, void* data)
    {
      s_platform_data[index] = data;
    }

  private:
    Platform() = delete;
    ~Platform() = delete;

    static constexpr Uint32 MAX_PLATFORM_DATA{ 5 };

    static const void* s_platform_data[];
  };
}

#if defined (CORVUS_PLATFORM_WIN32)
  #define CORVUS_PLATFORM_EVENT_POLL_TYPE Win32EventPoll

  #if defined(CORVUS_RENDERER_OPENGL)
    #define CORVUS_PLATFORM_GRAPHICS_CONTEXT_TYPE WGLContext
  #elif defined(CORVUS_RENDERER_DIRECT3D11)
    #define CORVUS_PLATFORM_GRAPHICS_CONTEXT_TYPE D3D11Context
  #endif

  #define CORVUS_PLATFORM_WINDOW_TYPE Win32Window
#else
  #define CORVUS_PLATFORM_EVENT_POLL_TYPE
  #define CORVUS_PLATFORM_GRAPHICS_CONTEXT_TYPE
  #define CORVUS_PLATFORM_WINDOW_TYPE
#endif
