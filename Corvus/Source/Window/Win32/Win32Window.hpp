#pragma once

#ifdef CORVUS_PLATFORM_WIN32

#include "../../Core/Types.hpp"
#include "../Window.hpp"

namespace Corvus
{
  class Win32Window : public Window
  {
  public:
    Win32Window(const char* title, Uint32 width, Uint32 height);
    ~Win32Window() override = default;

    inline const char* GetTitle() const override final { return m_data.title; }
    inline Uint32      GetWidth() const override final { return m_data.width; }
    inline Uint32      GetHeight() const override final { return m_data.height; }

  private:
    WindowData m_data;
  };
}

#endif
