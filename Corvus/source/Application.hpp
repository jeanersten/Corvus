#pragma once

#include "Core/Core.hpp"
#include "Event.hpp"
#include "GraphicsContext.hpp"
#include "Layer.hpp"
#include "Window.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace Corvus
{
  using LayerCollection = std::vector<std::unique_ptr<Layer>>;

  class CORVUS_API Application
  {
  public:
    Application();
    virtual ~Application() = default;

    void Run();

  protected:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<GraphicsContext> m_context;
    LayerCollection m_layers;
    LayerCollection m_overlays;

    virtual void Setup();
    virtual void Cleanup();

    template<typename T, typename... Args>
    T* PushLayer(Args&&... args)
    {
      auto layer{ std::make_unique<T>(std::forward<Args>(args)...) };
      T* raw{ layer.get() };

      layer->Attach();
      m_layers.emplace_back(std::move(layer));

      return raw;
    }

    void PopLayer(Layer* layer)
    {
      auto it{ std::find_if(m_layers.begin(), m_layers.end(),
               [layer](auto& ptr) { return ptr.get() == layer; }) };

      if (it != m_layers.end())
      {
        (*it)->Detach();
        m_layers.erase(it);
      }
    }

    template<typename T, typename... Args>
    T* PushOverlay(Args&&... args)
    {
      auto overlay{ std::make_unique<T>(std::forward<Args>(args)...) };
      T* raw{ overlay.get() };

      overlay->OnAttach();
      m_overlays.emplace_back(std::move(overlay));

      return raw;
    }

    void PopOverlay(Layer* overlay)
    {
      auto it{ std::find_if(m_overlays.begin(), m_overlays.end(),
               [overlay](auto& ptr) { return ptr.get() == overlay; }) };

      if (it != m_overlays.end())
      {
        (*it)->Detach();
        m_overlays.erase(it);
      }
    }

  private:
    void Update();
    void RespondEvent(Event& event);
  };
}
