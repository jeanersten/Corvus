#include "Application.hpp"
#include "Event.hpp"
#include <functional>

namespace Corvus
{
  Application::Application()
    : m_window(nullptr)
  {
    m_window = Window::Create(640, 480, L"Corvus Engine");
    m_window->SetEventCallback(std::bind(&Application::OnEvent, this,
                                         std::placeholders::_1));
  }

  Application::~Application()
  {
    delete m_window;
  }

  void Application::Run()
  {
    while (!m_window->ShouldClose())
    {
      m_window->PollEvents();
    }
  }
}
