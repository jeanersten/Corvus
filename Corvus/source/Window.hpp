#pragma once

#include "Core/Core.hpp"
#include "Event.hpp"
#include <memory>
#include <string>
#include <string_view>

namespace Corvus
{
  class CORVUS_API Window
  {
  public:
    Window() = default;
    virtual ~Window() = default;

    static std::unique_ptr<Window> Create(Uint32 width, Uint32 height,
                                          std::wstring_view title);

    virtual inline Uint32 GetWidth() const = 0;
    virtual inline Uint32 GetHeight() const = 0;
    virtual inline void* GetNativeWindow() const = 0;

    virtual inline bool ShouldClose() const = 0;

    virtual inline void SetEventCallback(EventCallbackFn callback) = 0;

  protected:
    struct WindowData
    {
      Uint32 width;
      Uint32 height;
      std::wstring title;
    };
  };
}
