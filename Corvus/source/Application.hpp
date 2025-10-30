#pragma once

#include "Core/Core.hpp"
#include "Event.hpp"
#include "Window.hpp"

namespace Corvus
{
  class CORVUS_API Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();

  protected:
    virtual void OnEvent(Event& event) = 0;

    Window* m_window;
  };
}
