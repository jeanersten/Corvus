#pragma once

#include "../Core/Core.hpp"
#include "../Core/Types.hpp"

namespace Corvus
{
  struct WindowData
  {
    const char* title { nullptr };
    Uint32 width { 0 };
    Uint32 height { 0 };

    WindowData() = default; 
    ~WindowData() = default;
  };

  class CORVUS_API Window
  {
  public:
    Window() = default;
    virtual ~Window() = default;

    static Window* Create(const char* title = "Corvus!", Uint32 width = 640, Uint32 height = 480);
    virtual inline const char* GetTitle() const = 0;
    virtual inline Uint32      GetWidth() const = 0;
    virtual inline Uint32      GetHeight() const = 0;
  };
}
