#pragma once

#if defined(CORVUS_PLATFORM_WIN32)

#include "Core/Core.hpp"
#include "GraphicsContext.hpp"
#include "Window.hpp"
#include <windows.h>
#include <functional>

namespace Corvus
{
  class Win32Window : public Window
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

    void PollEvents() override;

  private:
    static constexpr PCWSTR const CLASS_NAME { L"CorvusWindow" };

    WindowData m_data;
    bool m_should_close;

    EventCallbackFn m_callback;

    GraphicsContext* m_context;

    HWND m_handle;

    static LRESULT CALLBACK Callback(HWND handle, UINT msg_type,
                                     WPARAM wparam, LPARAM lparam);
    LRESULT HandleMessage(UINT msg_type, WPARAM wparam, LPARAM lparam);
  };
}

#endif
