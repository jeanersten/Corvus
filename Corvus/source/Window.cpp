#include "Win32Window.hpp"
#include "Window.hpp"

namespace Corvus
{
  Window* Window::Create(Uint32 width, Uint32 height, const wchar_t* title)
  {
    #ifdef CORVUS_PLATFORM_WIN32
      return new Win32Window(width, height, title);
    #endif
  }
}
