#include "Application.hpp"
#include "Event.hpp"
#include "Layer.hpp"
#include "Log.hpp"
#include <chrono>
#include <functional>
#include <thread>

namespace Corvus
{
  Application::Application()
    : m_window(nullptr)
    , m_layer_stack(nullptr)
  {
    m_window = Window::Create(640, 480, L"Corvus Engine");
    m_window->SetEventCallback(std::bind(&Application::OnEvent, this,
                                         std::placeholders::_1));

    m_layer_stack = new LayerStack();
  }

  Application::~Application()
  {
    delete m_window;
    delete m_layer_stack;
  }

  void Application::PushLayer(Layer* layer)
  {
    m_layer_stack->PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PopLayer(Layer* layer)
  {
    m_layer_stack->PopLayer(layer);
    layer->OnDetach();
  }

  void Application::PushOverlay(Layer* overlay)
  {
    m_layer_stack->PushOverlay(overlay);
    overlay->OnAttach();
  }

  void Application::PopOverlay(Layer* overlay)
  {
    m_layer_stack->PopOverlay(overlay);
    overlay->OnDetach();
  }
  
  void Application::OnSetup()
  {}

  void Application::OnCleanup()
  {}

  void Application::OnUpdate()
  {
    for (Layer* layer : m_layer_stack->GetLayers())
    {
      layer->OnUpdate();
    }
  }

  void Application::OnEvent(Event& event)
  {
    for (auto it = m_layer_stack->GetLayers().rbegin();
         it != m_layer_stack->GetLayers().rend(); it++)
    {
      (*it)->OnEvent(event);

      if (event.IsHandled()) break;
    }
  }

  void Application::Run()
  {
    OnSetup();

    while (!m_window->ShouldClose())
    {
      m_window->PollEvents();

      OnUpdate();

      // debugging purpose, better solution soon
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    OnCleanup();
  }
}
