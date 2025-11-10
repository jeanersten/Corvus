#include "Platform/Platform.hpp"
#include "GraphicsContext.hpp"
#include "Window.hpp"
#include <memory>

namespace Corvus
{
  std::unique_ptr<GraphicsContext> GraphicsContext::Create(Window* window)
  {
    return std::make_unique<CORVUS_PLATFORM_GRAPHICS_CONTEXT_TYPE>(window);
  }
}
