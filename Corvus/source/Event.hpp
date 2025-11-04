#pragma once

#include "Core/Core.hpp"
#include <functional>

namespace Corvus
{
  enum class EventType
  {
    None = 0,
    WindowCreated, WindowDestroyed,
    WindowGainedFocus, WindowLostFocus,
    WindowMoved, WindowResized,
    KeyboardKeyPressed, KeyboardKeyReleased,
    MouseButtonPressed, MouseButtonReleased
  };

  enum class EventCategory
  {
    None     = 0,
    Window   = CORVUS_BIT_MASK(0),
    Input    = CORVUS_BIT_MASK(1),
    Keyboard = CORVUS_BIT_MASK(2),
    Mouse    = CORVUS_BIT_MASK(3)
  };

  inline EventCategory operator&(EventCategory lhs, EventCategory rhs)
  {
    return static_cast<EventCategory>(
      static_cast<Uint32>(lhs) & static_cast<Uint32>(rhs)
    );
  }

  inline EventCategory operator|(EventCategory lhs, EventCategory rhs)
  {
    return static_cast<EventCategory>(
      static_cast<Uint32>(lhs) | static_cast<Uint32>(rhs)
    );
  }

  class Event
  {
    friend class EventDispatcher;

  public:
    inline bool IsHandled()
    {
      return m_handled;
    }

    inline bool IsInCategory(EventCategory category)
    {
      return static_cast<bool>(GetCategory() & category);
    }

    virtual inline EventType GetType() const = 0;
    virtual inline EventCategory GetCategory() const = 0;

  protected:
    Event();
    virtual ~Event() = default;

    bool m_handled;
  };

  class CORVUS_API EventDispatcher
  {
    template<typename T>
    using EventFn = std::function<bool(T&)>;

  public:
    EventDispatcher(Event& event);
    ~EventDispatcher() = default;

    // send event message if event type matches static type
    template<typename T>
    bool Send(EventFn<T> callback)
    {
      if (m_event.GetType() == T::GetStaticType())
      {
        m_event.m_handled = callback(*(T*)&m_event);

        return true;
      }

      return false;
    }

  private:
    Event& m_event;
  };

  class CORVUS_API WindowCreatedEvent : public Event
  {
  public:
    WindowCreatedEvent() = default;
    ~WindowCreatedEvent() override = default;

    inline static EventType GetStaticType()
    {
      return EventType::WindowCreated;
    }

    inline EventType GetType() const override
    {
      return GetStaticType();
    }

    inline EventCategory GetCategory() const override
    {
      return EventCategory::Window;
    }
  };

  class CORVUS_API WindowDestroyedEvent : public Event
  {
  public:
    WindowDestroyedEvent() = default;
    ~WindowDestroyedEvent() override = default;

    inline static EventType GetStaticType()
    {
      return EventType::WindowDestroyed;
    }

    inline EventType GetType() const override
    {
      return GetStaticType();
    }

    inline EventCategory GetCategory() const override
    {
      return EventCategory::Window;
    }
  };

  class CORVUS_API WindowGainedFocusEvent : public Event
  {
  public:
    WindowGainedFocusEvent() = default;
    ~WindowGainedFocusEvent() override = default;

    inline static EventType GetStaticType()
    {
      return EventType::WindowGainedFocus;
    }

    inline EventType GetType() const override
    {
      return GetStaticType();
    }

    inline EventCategory GetCategory() const override
    {
      return EventCategory::Window;
    }
  };

  class CORVUS_API WindowLostFocusEvent : public Event
  {
  public:
    WindowLostFocusEvent() = default;
    ~WindowLostFocusEvent() override = default;

    inline static EventType GetStaticType()
    {
      return EventType::WindowLostFocus;
    }

    inline EventType GetType() const override
    {
      return GetStaticType();
    }

    inline EventCategory GetCategory() const override
    {
      return EventCategory::Window;
    }
  };

  class CORVUS_API WindowMovedEvent : public Event
  {
  public:
    WindowMovedEvent(Uint32 x, Uint32 y);
    ~WindowMovedEvent() override = default;

    inline static EventType GetStaticType()
    {
      return EventType::WindowMoved;
    }

    inline EventType GetType() const override
    {
      return GetStaticType();
    }

    inline EventCategory GetCategory() const override
    {
      return EventCategory::Window;
    }

    inline Uint32 GetX() const
    {
      return m_x;
    }

    inline Uint32 GetY() const
    {
      return m_y;
    }

  private:
    Uint32 m_x;
    Uint32 m_y;
  };

  class CORVUS_API WindowResizedEvent : public Event
  {
  public:
    WindowResizedEvent(Uint32 width, Uint32  height);
    ~WindowResizedEvent() override = default;

    inline static EventType GetStaticType()
    {
      return EventType::WindowResized;
    }

    inline EventType GetType() const override
    {
      return GetStaticType();
    }

    inline EventCategory GetCategory() const override
    {
      return EventCategory::Window;
    }

    inline Uint32 GetWidth() const
    {
      return m_width;
    }

    inline Uint32 GetHeight() const
    {
      return m_height;
    }

  private:
    Uint32 m_width;
    Uint32 m_height;
  };

  class CORVUS_API KeyboardKeyPressedEvent : public Event
  {
  public:
    KeyboardKeyPressedEvent(Uint32 key_code,
                            bool is_repeated);
    ~KeyboardKeyPressedEvent() override = default;

    inline static EventType GetStaticType()
    {
      return EventType::KeyboardKeyPressed;
    }

    inline EventType GetType() const override
    {
      return GetStaticType();
    }

    inline EventCategory GetCategory() const override
    {
      return (EventCategory::Input | EventCategory::Keyboard);
    }

    inline bool IsRepeated() const
    {
      return m_is_repeated;
    }

  private:
    Uint32 m_key_code;
    bool m_is_repeated;
  };

  class CORVUS_API KeyboardKeyReleasedEvent : public Event
  {
  public:
    KeyboardKeyReleasedEvent(Uint32 key_code);
    ~KeyboardKeyReleasedEvent() override = default;

    inline static EventType GetStaticType()
    {
      return EventType::KeyboardKeyReleased;
    }

    inline EventType GetType() const override
    {
      return GetStaticType();
    }

    inline EventCategory GetCategory() const override
    {
      return (EventCategory::Input | EventCategory::Keyboard);
    }

  private:
    Uint32 m_key_coode;
  };

  class CORVUS_API MouseButtonPressedEvent : public Event
  {
  public:
    MouseButtonPressedEvent(Uint32 button_code);
    ~MouseButtonPressedEvent() override = default;

    inline static EventType GetStaticType()
    {
      return EventType::MouseButtonPressed;
    }

    inline EventType GetType() const override
    {
      return GetStaticType();
    }

    inline EventCategory GetCategory() const override
    {
      return (EventCategory::Input | EventCategory::Mouse);
    }

  private:
    Uint32 m_button_code;
  };

  class CORVUS_API MouseButtonReleasedEvent : public Event
  {
  public:
    MouseButtonReleasedEvent(Uint32 button_code);
    ~MouseButtonReleasedEvent() override = default;

    inline static EventType GetStaticType()
    {
      return EventType::MouseButtonReleased;
    }

    inline EventType GetType() const override
    {
      return GetStaticType();
    }

    inline EventCategory GetCategory() const override
    {
      return (EventCategory::Input | EventCategory::Mouse);
    }

  private:
    Uint32 m_button_code;
  };

  using EventCallbackFn = std::function<void(Event&)>;
}
