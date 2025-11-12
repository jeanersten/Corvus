#if defined(CORVUS_RENDERER_OPENGL) && defined(CORVUS_PLATFORM_WIN32)

#include "../Core/PCH.hpp"
#include "../Core/Core.hpp"
#include "../Log.hpp"
#include "../Window.hpp"
#include "Platform.hpp"
#include "OpenGLContext.hpp"

#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001
#define WGL_DRAW_TO_WINDOW_ARB            0x2001
#define WGL_ACCELERATION_ARB              0x2003
#define WGL_SUPPORT_OPENGL_ARB            0x2010
#define WGL_DOUBLE_BUFFER_ARB             0x2011
#define WGL_PIXEL_TYPE_ARB                0x2013
#define WGL_COLOR_BITS_ARB                0x2014
#define WGL_DEPTH_BITS_ARB                0x2022
#define WGL_STENCIL_BITS_ARB              0x2023
#define WGL_FULL_ACCELERATION_ARB         0x2027
#define WGL_TYPE_RGBA_ARB                 0x202B

typedef HGLRC (WINAPI *PFNWGLCREATECONTEXTATTRIBSARBPROC)
(HDC hDC, HGLRC hShareContext, const int *attribList);
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB{ nullptr };

typedef BOOL (WINAPI *PFNWGLCHOOSEPIXELFORMATARBPROC)
(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList,
 UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB{ nullptr };

namespace Corvus
{
  WGLContext::WGLContext(Window* window)
    : m_window(window)
    , m_dc(NULL)
    , m_glrc(NULL)
  {
    m_dc = GetDC(static_cast<HWND>(m_window->GetNativeWindow()));
  }

  LRESULT CALLBACK WGLContext::TempWndProc(HWND wnd_handle, UINT msg_type,
                                           WPARAM wparam, LPARAM lparam)
  {
    LRESULT result = 0;

    switch (msg_type)
    {
      case WM_CLOSE:
      {
        DestroyWindow(wnd_handle);
      }
      break;

      case WM_DESTROY:
      {
        PostQuitMessage(0);
      }
      break;

      default:
      {
        result = DefWindowProcA(wnd_handle, msg_type, wparam, lparam);
      }
      break;
    }

    return result;
  }

  void WGLContext::LoadExtensions() const
  {
    WNDCLASS wc_temp{ };
    HINSTANCE instance{ *Platform::GetDataPointer<HINSTANCE>(1) };

    wc_temp.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc_temp.lpfnWndProc = TempWndProc;
    wc_temp.hInstance = instance;
    wc_temp.lpszClassName = L"CORVUSTempWGLWindow";

    if (!RegisterClass(&wc_temp))
    {
      CORVUS_LOG_FATAL("Failed to register temporary WGL window!");
    }

    HWND wnd_temp{ CreateWindowEx(0, wc_temp.lpszClassName, L"TempWindow", 0,
                                  CW_USEDEFAULT, CW_USEDEFAULT,
                                  CW_USEDEFAULT, CW_USEDEFAULT,
                                  NULL, NULL, instance, nullptr) };

    if (wnd_temp == NULL)
    {
      CORVUS_LOG_FATAL("Failed to create temporary WGL window!");
    }

    HDC dc_temp{ GetDC(wnd_temp) };
    PIXELFORMATDESCRIPTOR pf_desc{ };

    pf_desc.nSize = sizeof(pf_desc);
    pf_desc.nVersion = 1;
    pf_desc.iPixelType = PFD_TYPE_RGBA;
    pf_desc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                      PFD_DOUBLEBUFFER;
    pf_desc.cColorBits = 32;
    pf_desc.cAlphaBits = 8;
    pf_desc.iLayerType = PFD_MAIN_PLANE;
    pf_desc.cDepthBits = 24;
    pf_desc.cStencilBits = 8;

    Int32 pixel_format{ ChoosePixelFormat(dc_temp, &pf_desc) };

    if (!pixel_format)
    { 
      CORVUS_LOG_FATAL("Failed to find suitable pixel format!");
    }

    if (!SetPixelFormat(dc_temp, pixel_format, &pf_desc))
    {
      CORVUS_LOG_FATAL("Failed to set pixel format!");
    }

    HGLRC glrc_temp{ wglCreateContext(dc_temp) };

    if (glrc_temp == NULL)
    {
      CORVUS_LOG_FATAL("Failed to create inital OpenGL context!");
    }

    if (!wglMakeCurrent(dc_temp, glrc_temp))
    {
      CORVUS_LOG_FATAL("Failed to activate OpenGL context!");
    }

    wglCreateContextAttribsARB =
    reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>
    (wglGetProcAddress("wglCreateContextAttribsARB"));

    wglChoosePixelFormatARB =
    reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>
    (wglGetProcAddress("wglChoosePixelFormatARB"));

    wglMakeCurrent(dc_temp, NULL);
    wglDeleteContext(glrc_temp);
    ReleaseDC(wnd_temp, dc_temp);
  }

  void WGLContext::Init()
  {
    LoadExtensions();

    int pixel_format_attribs[]{
      WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
      WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
      WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
      WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
      WGL_COLOR_BITS_ARB,     32,
      WGL_DEPTH_BITS_ARB,     24,
      WGL_STENCIL_BITS_ARB,   8,
      0
    };

    Int32 pixel_format{ };
    Uint32 format_count{ };

    wglChoosePixelFormatARB(m_dc, pixel_format_attribs, 0, 1,
                            &pixel_format, &format_count);

    if (!format_count)
    {
      CORVUS_LOG_ERR("Failed to load OpenGL 3.3 pixel format!");
    }

    PIXELFORMATDESCRIPTOR pf_desc{ };

    DescribePixelFormat(m_dc, pixel_format, sizeof(pf_desc), &pf_desc);

    if (!SetPixelFormat(m_dc, pixel_format, &pf_desc))
    {
      CORVUS_LOG_ERR("Failed to set OpenGL 3.3 rendering context!");
    }

    int gl33_attribs[]{
      WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      WGL_CONTEXT_MINOR_VERSION_ARB, 3,
      WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      0,
    };

    m_glrc = wglCreateContextAttribsARB(m_dc, 0, gl33_attribs);

    if (m_glrc == NULL)
    {
      CORVUS_LOG_ERR("Failed to create OpenGL 3.3 rendering context!");
    }

    if (!wglMakeCurrent(m_dc, m_glrc))
    {
      CORVUS_LOG_ERR("Failed to activate OpenGL 3.3 rendering context!");
    }

    if (!gladLoadGL())
    {
      CORVUS_LOG_ERR("Failed to load OpenGL functions via GLAD!");
    }
  }

  void WGLContext::ResizeBuffers(Uint32 width, Uint32 height)
  {
    glViewport(0, 0 ,width, height);
  }

  void WGLContext::SwapBuffers()
  {
    // TODO: Move buffer clear color somewhere safer.

    glClearColor(0.22f, 0.54f, 0.65f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);

    ::SwapBuffers(m_dc);
  }
}

#endif
