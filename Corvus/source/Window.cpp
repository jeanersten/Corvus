#include "Core/PCH.hpp"
#include "Core/Core.hpp"
#include "Platform/Platform.hpp"
#include "Window.hpp"

namespace Corvus
{
  std::unique_ptr<Window> Window::Create(Uint32 width, Uint32 height,
                                         const wchar_t* title)
  {
    return std::make_unique<CORVUS_PLATFORM_WINDOW_TYPE>(width, height, title);
  }
}
