#include <Corvus/Engine.hpp>

class Sandbox : public Corvus::Application
{
public:
  Sandbox() = default;
  ~Sandbox() override = default;

protected:
  void OnEvent(Corvus::Event& event) override
  {
    using namespace Corvus;

    EventDispatcher dispatcher { event };

    dispatcher.Send<WindowGainedFocusEvent>(
    [](WindowGainedFocusEvent& event){
      CORVUS_LOG_TRACE("Window gained focus.");

      return false;
    });

    dispatcher.Send<WindowLostFocusEvent>(
    [](WindowLostFocusEvent& event){
      CORVUS_LOG_TRACE("Window lost focus.");

      return false;
    });

    dispatcher.Send<WindowMovedEvent>(
    [](WindowMovedEvent& event){
      CORVUS_LOG_TRACE("Window have been moved to: x: {}, y: {}.",
                       event.GetX(), event.GetY());

      return false;
    });

    dispatcher.Send<WindowResizedEvent>(
    [](WindowResizedEvent& event){
      CORVUS_LOG_TRACE("Window have been resized to: width: {}, height : {}",
                       event.GetWidth(), event.GetHeight());

      return false;
    });

    dispatcher.Send<KeyboardKeyPressedEvent>(
    [](KeyboardKeyPressedEvent& event){
      CORVUS_LOG_TRACE("A keyboard key have been pressed.");

      return false;
    });

    dispatcher.Send<KeyboardKeyReleasedEvent>(
    [](KeyboardKeyReleasedEvent& event){
      CORVUS_LOG_TRACE("A keyboard key have been released.");

      return false;
    });

    dispatcher.Send<MouseButtonPressedEvent>(
    [](MouseButtonPressedEvent& event){
      CORVUS_LOG_TRACE("A mouse button have been pressed.");

      return false;
    });

    dispatcher.Send<MouseButtonReleasedEvent>(
    [](MouseButtonReleasedEvent& event){
      CORVUS_LOG_TRACE("A mouse button have been released.");

      return false;
    });
  }
};

CORVUS_REGISTER_APPLICATION_ENTRY(Sandbox);
