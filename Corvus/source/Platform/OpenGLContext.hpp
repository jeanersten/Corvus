#pragma once

#if defined(CORVUS_RENDERER_OPENGL) && defined(CORVUS_PLATFORM_WIN32)

#include "../Core/Core.hpp"
#include "../GraphicsContext.hpp"
#include "../Window.hpp"
#include <windows.h>

namespace Corvus
{
  class WGLContext final : public GraphicsContext
  {
  public:
    WGLContext(Window* window);
    ~WGLContext() = default;

    void Init() override;
    void ResizeBuffers(Uint32 width, Uint32 height) override;
    void SwapBuffers() override;

  private:
    Window* m_window;
    HDC m_dc;
    HGLRC m_glrc;

    static LRESULT CALLBACK TempWndProc(HWND wnd_handle, UINT msg_type,
                                        WPARAM wparam, LPARAM lparam);
    void LoadExtensions() const;
  };
}

#endif
