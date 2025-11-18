#pragma once

#include "Core/Core.hpp"
#include "Window.hpp"

namespace Corvus
{
  class CORVUS_API DebugPanel
  {
  public:
    DebugPanel() = default;
    ~DebugPanel() = default;

    void Start(Window* window);
    void Update();
    void Render();
  };
}
