#if defined(CORVUS_PLATFORM_WIN32)

#include "../Core/PCH.hpp"
#include "../Core/Core.hpp"
#include "../Event.hpp"
#include "Platform.hpp"
#include "Win32Window.hpp"
#include <imgui/imgui.h>

extern IMGUI_IMPL_API ::LRESULT
ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg,
                               WPARAM wParam, LPARAM lParam);

namespace Corvus
{

  Win32Window::Win32Window(Uint32 width, Uint32 height, std::wstring_view title)
    : m_data()
    , m_should_close(false)
    , m_callback(nullptr)
    , m_handle(NULL)
  {
    m_data.width = width;
    m_data.height = height;
    m_data.title = title;

    WNDCLASS wnd_class{ };
    HINSTANCE instance{ *Platform::GetDataPointer<HINSTANCE>(1) };

    wnd_class.style = CS_OWNDC;
    wnd_class.lpfnWndProc = Callback;
    wnd_class.hInstance = instance;
    wnd_class.lpszClassName = CLASS_NAME;

    RegisterClass(&wnd_class);

    RECT wnd_rect{ 0, 0,
                   static_cast<LONG>(m_data.width),
                   static_cast<LONG>(m_data.height) };

    AdjustWindowRect(&wnd_rect, WS_OVERLAPPEDWINDOW, FALSE);

    Uint32 wnd_width{ static_cast<Uint32>(wnd_rect.right - wnd_rect.left) };
    Uint32 wnd_height{ static_cast<Uint32>(wnd_rect.bottom - wnd_rect.top) };

    m_handle = CreateWindowEx(0, CLASS_NAME, m_data.title.c_str(),
                              WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, CW_USEDEFAULT,
                              wnd_width, wnd_height,
                              NULL, NULL, instance, this);

    ShowWindow(m_handle, *Platform::GetDataPointer<int>(3));
  }


  LRESULT Win32Window::Callback(HWND handle, UINT msg_type,
                                WPARAM wparam, LPARAM lparam)
  {
    Win32Window* wnd_ptr{ nullptr };

    if (msg_type == WM_NCCREATE)
    {
      CREATESTRUCT* data_ptr{ reinterpret_cast<CREATESTRUCT*>(lparam) };

      wnd_ptr = reinterpret_cast<Win32Window*>(data_ptr->lpCreateParams);

      SetWindowLongPtr(handle, GWLP_USERDATA,
                       reinterpret_cast<LONG_PTR>(wnd_ptr));

      wnd_ptr->m_handle = handle;
    }
    else
    {
      wnd_ptr = reinterpret_cast<Win32Window*>
                 (GetWindowLongPtr(handle, GWLP_USERDATA));
    }

    if (wnd_ptr != nullptr)
    {
      return wnd_ptr->HandleMessage(msg_type, wparam, lparam);
    }
    else
    {
      return DefWindowProc(handle, msg_type, wparam, lparam);
    }
  }

  LRESULT Win32Window::HandleMessage(UINT msg_type,
                                     WPARAM wparam, LPARAM lparam)
  {
    LRESULT result{ 0 };

    ImGui_ImplWin32_WndProcHandler(m_handle, msg_type, wparam, lparam);

    switch(msg_type)
    {
      case WM_CREATE:
      {
        WindowCreatedEvent event{ };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_CLOSE:
      {
        DestroyWindow(m_handle);
        m_should_close = true;
      }
      break;

      case WM_DESTROY:
      {
        WindowDestroyedEvent event{ };

        if (m_callback) m_callback(event);

        PostQuitMessage(0);
      }
      break;

      case WM_SETFOCUS:
      {
        WindowGainedFocusEvent event{ };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_KILLFOCUS:
      {
        WindowLostFocusEvent event{ };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_MOVE:
      {
        WindowMovedEvent event{ LOWORD(lparam), HIWORD(lparam) };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_SIZE:
      {
        WindowResizedEvent event{ LOWORD(lparam), HIWORD(lparam) };

        m_data.width = event.GetWidth();
        m_data.height = event.GetHeight();

        if (m_callback) m_callback(event);
      }
      break;

      // TODO: Implement better key identification and input system.

      case WM_KEYDOWN:
      {
        bool is_repeated{ (lparam & (static_cast<long long>(1) << 30)) != 0 };
        KeyboardKeyPressedEvent event{ (Uint32)wparam, is_repeated };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_KEYUP:
      {
        KeyboardKeyReleasedEvent event{ (Uint32)wparam };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_LBUTTONDOWN:
      {
        MouseButtonPressedEvent event{ VK_LBUTTON };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_LBUTTONUP:
      {
        MouseButtonReleasedEvent event{ VK_LBUTTON };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_RBUTTONDOWN:
      {
        MouseButtonPressedEvent event{ VK_RBUTTON };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_RBUTTONUP:
      {
        MouseButtonReleasedEvent event{ VK_RBUTTON };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_MBUTTONDOWN:
      {
        MouseButtonPressedEvent event{ VK_MBUTTON };

        if (m_callback) m_callback(event);
      }
      break;

      case WM_MBUTTONUP:
      {
        MouseButtonReleasedEvent event{ VK_MBUTTON };

        if (m_callback) m_callback(event);
      }
      break;

      default:
      {
        result = DefWindowProc(m_handle, msg_type, wparam, lparam);
      }
      break;
    }

    return result;
  }
}

#endif
