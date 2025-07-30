#ifdef CORVUS_PLATFORM_WIN32

#include "../../Core/Types.hpp"
#include "Win32Window.hpp"
#include <Windows.h>
#include <cstddef>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace Corvus
{
  Win32Window::Win32Window(const char* title, Uint32 width, Uint32 height)
    : Window()
  {
    m_data.title = title;
    m_data.width = width;
    m_data.height = height;

    LPCSTR window_class_name { "CORVUSWindow" };

    WNDCLASSEX window_class { };
    window_class.cbSize = sizeof(WNDCLASSEX);
    window_class.lpfnWndProc = WindowProc;
    window_class.hInstance = GetModuleHandle(NULL);
    window_class.lpszClassName = window_class_name;
    RegisterClassEx(&window_class);

    DWORD window_style { WS_OVERLAPPEDWINDOW };
    RECT window_rect {0, 0, static_cast<LONG>(m_data.width), static_cast<LONG>(m_data.height)};
    AdjustWindowRectEx(&window_rect, window_style, FALSE, 0);

    HWND hwnd { };
    hwnd = CreateWindowEx(0, window_class_name, m_data.title, window_style,
                               CW_USEDEFAULT, CW_USEDEFAULT,
                               window_rect.right - window_rect.left, window_rect.bottom - window_rect.top,
                               NULL, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow(hwnd, SW_SHOW);

    MSG msg { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch (msg)
  {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    
    case WM_PAINT:
      {
        PAINTSTRUCT ps { };
        HDC hdc { BeginPaint(hwnd, &ps) };
        HBRUSH brush { CreateSolidBrush(RGB(90, 140, 123)) };
        FillRect(hdc, &ps.rcPaint, brush);
        EndPaint(hwnd, &ps);
      }
      return 0;
  }

  return DefWindowProc(hwnd, msg, wparam, lparam);
}

#endif
