#pragma once

#if defined(CORVUS_PLATFORM_WIN32)

#include "../Core/Core.hpp"
#include "../Event.hpp"
#include "../Window.hpp"
#include <windows.h>
#include <cwchar>

namespace Corvus
{
  class Win32Window final : public Window
  {
  public:
    Win32Window(Uint32 width, Uint32 height, const wchar_t* title);
    ~Win32Window() override = default;

    inline Uint32 GetWidth() const override
    {
      return m_data.width;
    }

    inline Uint32 GetHeight() const override
    {
      return m_data.height;
    }

    inline void* GetNativeWindow() const override
    {
      return static_cast<void*>(m_handle);
    }

    inline bool ShouldClose() const override
    {
      return m_should_close;
    }

    inline void SetEventCallback(EventCallbackFn callback) override
    {
      m_callback = callback;
    }

  private:
    static constexpr PCWSTR CLASS_NAME{ L"CorvusWindow" };

    WindowData m_data;
    bool m_should_close;
    EventCallbackFn m_callback;
    HWND m_handle;

    static LRESULT CALLBACK Callback(HWND handle, UINT msg_type,
                                     WPARAM wparam, LPARAM lparam);
    LRESULT HandleMessage(UINT msg_type,
                          WPARAM wparam, LPARAM lparam);
  };
}

#endif
