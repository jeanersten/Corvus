#include "../Core/Types.hpp"
#include "Window.hpp"
#include "Win32/Win32Window.hpp"

namespace Corvus
{
  Window* Window::Create(const char* title, Uint32 width, Uint32 height)
  {
    #ifdef CORVUS_PLATFORM_WIN32

      return new Win32Window(title, width, height);

    #endif
  }
}
