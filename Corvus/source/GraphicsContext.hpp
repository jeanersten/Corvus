#pragma once

#include "Core/Core.hpp"
#include "Window.hpp"

namespace Corvus
{
  class CORVUS_API GraphicsContext
  {
  public:
    GraphicsContext() = default;
    virtual ~GraphicsContext() = default;

    static GraphicsContext* Create(Window* window);

    virtual void Init() = 0;
    virtual void ResizeBuffers() = 0;
    virtual void SwapBuffers() = 0;
  };
}
