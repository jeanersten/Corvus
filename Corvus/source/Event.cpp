#include "Core/Core.hpp"
#include "Event.hpp"

namespace Corvus
{
  Event::Event()
    : m_handled(false)
  {}

  EventDispatcher::EventDispatcher(Event& event)
    : m_event(event)
  {}

  WindowMovedEvent::WindowMovedEvent(Uint32 x, Uint32 y)
    : m_x(x)
    , m_y(y)
  {}

  WindowResizedEvent::WindowResizedEvent(Uint32 width, Uint32 height)
    : m_width(width)
    , m_height(height)
  {}

  KeyboardKeyPressedEvent::KeyboardKeyPressedEvent(Uint32 key_code,
                                                   bool is_repeated)
    : m_key_code(key_code)
    , m_is_repeated(is_repeated)
  {}

  KeyboardKeyReleasedEvent::KeyboardKeyReleasedEvent(Uint32 key_code)
    : m_key_coode(key_code)
  {}

  MouseButtonPressedEvent::MouseButtonPressedEvent(Uint32 button_code)
    : m_button_code(button_code)
  {}

  MouseButtonReleasedEvent::MouseButtonReleasedEvent(Uint32 button_code)
    : m_button_code(button_code)
  {}
}
