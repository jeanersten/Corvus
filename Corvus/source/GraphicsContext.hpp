#pragma once

#include "Core/Core.hpp"
#include "Window.hpp"
#include <memory>

namespace Corvus
{
  class CORVUS_API GraphicsContext
  {
  public:
    GraphicsContext() = default;
    virtual ~GraphicsContext() = default;

    static std::unique_ptr<GraphicsContext> Create(Window* window);

    virtual void Init() = 0;
    virtual void ResizeBuffers(Uint32 width, Uint32 height) = 0;
    virtual void SwapBuffers() = 0;
  };
}
