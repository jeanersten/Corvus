#include "D3D11Context.hpp"
#include "GraphicsContext.hpp"
#include "Window.hpp"

namespace Corvus
{
  GraphicsContext* GraphicsContext::Create(Window* window)
  {
    #if defined(CORVUS_RENDERER_DIRECT3D11) && defined(CORVUS_PLATFORM_WIN32)
      return new D3D11Context(window);
    #endif
  }
}
