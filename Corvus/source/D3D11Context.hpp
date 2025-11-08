#pragma once

#if defined(CORVUS_RENDERER_DIRECT3D11) && defined(CORVUS_PLATFORM_WIN32)

#include "Core/Core.hpp"
#include "GraphicsContext.hpp"
#include "Window.hpp"
#include <d3d11.h>
#include <dxgi.h>
#include <windows.h>
#include <wrl.h>

namespace Corvus
{
  class D3D11Context : public GraphicsContext
  {
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

  public:
    D3D11Context(Window* window);
    ~D3D11Context() override = default;

    void Init() override;
    void ResizeBuffers() override;
    void SwapBuffers() override;
  
  private:
    Window* m_window;
    ComPtr<ID3D11Device> m_device;
    ComPtr<ID3D11DeviceContext> m_device_context;
    ComPtr<ID3D11RenderTargetView> m_render_target;
    ComPtr<IDXGIFactory> m_factory;
    ComPtr<IDXGISwapChain> m_swap_chain;

    void CreateSwapChainResources();
    void DestroySwapChainResources();
  };
}

#endif
