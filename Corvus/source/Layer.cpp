#include "Layer.hpp"
#include <algorithm>
#include <string>

namespace Corvus
{
  Layer::Layer(const std::string& name)
    : m_name(name)
  {}

  LayerStack::LayerStack()
   : m_layers()
   , m_layer_index()
  {
    m_layer_index = m_layers.begin();
  }

  LayerStack::~LayerStack()
  {
    for (Layer* layer : m_layers)
    {
      delete layer;
    }
  }

  void LayerStack::PushLayer(Layer* layer)
  {
    m_layer_index = m_layers.emplace(m_layer_index, layer);
  }

  void LayerStack::PopLayer(Layer* layer)
  {
    auto it { std::find(m_layers.begin(), m_layers.end(), layer) };

    if (it != m_layers.end())
    {
      m_layers.erase(it);
      m_layer_index--;
    }
  }

  void LayerStack::PushOverlay(Layer* overlay)
  {
    m_layers.emplace_back(overlay);
  }

  void LayerStack::PopOverlay(Layer* overlay)
  {
    auto it { std::find(m_layers.begin(), m_layers.end(), overlay) };

    if (it != m_layers.end())
    {
      m_layers.erase(it);
    }
  }
}
