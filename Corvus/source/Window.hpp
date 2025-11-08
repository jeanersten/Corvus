#pragma once

#include "Core/Core.hpp"
#include "Event.hpp"

namespace Corvus
{
  class CORVUS_API Window
  {
  public:
    Window() = default;
    virtual ~Window() = default;

    static Window* Create(Uint32 width, Uint32 height, const wchar_t* title);

    virtual inline Uint32 GetWidth() const = 0;
    virtual inline Uint32 GetHeight() const = 0;
    virtual inline void* GetNativeWindow() const = 0;
    virtual inline bool ShouldClose() const = 0;

    virtual inline void SetEventCallback(EventCallbackFn callback) = 0;

    virtual void PollEvents() = 0;

  protected:
    struct WindowData
    {
      Uint32 width;
      Uint32 height;
      const wchar_t* title;
    };
  };
}
