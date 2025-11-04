#pragma once

#include "Core/Core.hpp"
#include "Event.hpp"
#include "Layer.hpp"
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
    void PushLayer(Layer* layer);
    void PopLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopOverlay(Layer* overlay);

    virtual void OnSetup();
    virtual void OnCleanup();
    virtual void OnUpdate();
    virtual void OnEvent(Event& event);

    Window* m_window;
    LayerStack* m_layer_stack;
  };
}
