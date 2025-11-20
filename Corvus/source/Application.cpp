#include "Core/PCH.hpp"
#include "Application.hpp"
#include "Event.hpp"
#include "Layer.hpp"
#include "Log.hpp"

namespace Corvus
{
  Application::Application()
    : m_window(nullptr)
    , m_context(nullptr)
    , m_layers()
    , m_overlays()
    , m_dbg_panel()
  {}

  void Application::Update()
  {
    for (auto& overlay : m_overlays) overlay->Update();
    for (auto& layer : m_layers) layer->Update();

    m_dbg_panel.Update();
  }

  void Application::Render()
  {
    m_dbg_panel.Render();

    // TODO: Implement rendering class to handle this instead.
    m_context->SwapBuffers();
  }

  void Application::RespondEvent(Event& event)
  {
    EventDispatcher dispatcher{ event };

    dispatcher.Send<WindowResizedEvent>([this](auto& event){
      m_context->ResizeBuffers(event.GetWidth(), event.GetHeight());

      return false;
    });

    for (auto it = m_overlays.rbegin(); it != m_overlays.rend(); it++)
    {
      if (event.IsHandled()) break;

      (*it)->RespondEvent(event);
    }

    for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++)
    {
      if (event.IsHandled()) break;

      (*it)->RespondEvent(event);
    }
  }

  void Application::Setup()
  {
    CORVUS_SET_CLIENT_LOG_LEVEL(LogLevel::Trace);
    CORVUS_SET_ENGINE_LOG_LEVEL(LogLevel::Trace);

    m_window = Window::Create(640, 480, L"Corvus Engine");
    m_window->SetEventCallback(std::bind(&Application::RespondEvent, this,
                               std::placeholders::_1));

    m_context = GraphicsContext::Create(m_window.get());
    m_context->Init();

    m_dbg_panel.Start(m_window.get());
  }

  void Application::Cleanup()
  {
    for (auto& overlay : m_overlays) overlay->Detach();
    m_overlays.clear();

    for (auto& layer : m_layers) layer->Detach();
    m_layers.clear();
  }

  void Application::Run()
  {
    Setup();

    while (!m_window->ShouldClose())
    {
      Event::Poll();

      Update();
      Render();

      // HACK: Debugging purpose, find a better solution soon.
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    Cleanup();
  }
}
