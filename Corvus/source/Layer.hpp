#pragma once

#include "Core/Core.hpp"
#include "Event.hpp"
#include <string>
#include <vector>

namespace Corvus
{
  class CORVUS_API Layer
  {
  public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer() = default;

    inline const std::string& GetName() const
    {
      return m_name;
    }

    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnEvent(Event& event) = 0;

  protected:
    std::string m_name;
  };

  class CORVUS_API LayerStack
  {
  public:
    LayerStack();
    ~LayerStack();

    inline const std::vector<Layer*>& GetLayers()
    {
      return m_layers;
    }

    void PushLayer(Layer* layer);
    void PopLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopOverlay(Layer* overlay);

  private:
    std::vector<Layer*> m_layers;
    std::vector<Layer*>::iterator m_layer_index;
  };
}
