#if defined(CORVUS_RENDERER_DIRECT3D11) && defined(CORVUS_PLATFORM_WIN32)

#include "../Core/PCH.hpp"
#include "../Log.hpp"
#include "../Window.hpp"
#include "D3D11Context.hpp"

namespace Corvus
{
  D3D11Context::D3D11Context(Window* window)
    : m_window(window)
    , m_device(nullptr)
    , m_device_context(nullptr)
    , m_render_target(nullptr)
    , m_factory(nullptr)
    , m_swap_chain(nullptr)
  {}

  void D3D11Context::Init()
  {
    if (FAILED(CreateDXGIFactory(IID_PPV_ARGS(&m_factory))))
    {
      CORVUS_LOG_FATAL("Failed to create DXGI Factory");

      return;
    }

    constexpr D3D_FEATURE_LEVEL feature_level{ D3D_FEATURE_LEVEL_11_0 };

    UINT flags{ 0 };

    #if defined(CORVUS_DEBUG)
      flags |= D3D11_CREATE_DEVICE_DEBUG;
    #endif

    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                 flags, &feature_level, 1, D3D11_SDK_VERSION,
                                 &m_device, nullptr, &m_device_context)))
    {
      CORVUS_LOG_FATAL("Failed to create device and device context");

      return;
    }

    DXGI_SWAP_CHAIN_DESC sc_desc{ };

    ZeroMemory(&sc_desc, sizeof(sc_desc));

    sc_desc.BufferDesc.Width = m_window->GetWidth();
    sc_desc.BufferDesc.Height = m_window->GetHeight();
    sc_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sc_desc.SampleDesc.Count = 1;
    sc_desc.SampleDesc.Quality = 0;
    sc_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sc_desc.BufferCount = 2;
    sc_desc.OutputWindow = static_cast<HWND>(m_window->GetNativeWindow());
    sc_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sc_desc.Windowed = TRUE;

    if (FAILED(m_factory->CreateSwapChain(m_device.Get(), &sc_desc,
                                          &m_swap_chain)))
    {
      CORVUS_LOG_FATAL("Failed to create swap chain");

      return;
    }

    CreateSwapChainResources();
  }

  void D3D11Context::ResizeBuffers(Uint32 width, Uint32 height)
  {
    m_device_context->Flush();

    DestroySwapChainResources();

    if (FAILED(m_swap_chain->ResizeBuffers(0, width, height,
                                           DXGI_FORMAT_B8G8R8A8_UNORM, 0)))
    {
      CORVUS_LOG_FATAL("Failed to resize swap chain buffers");

      return;
    }

    CreateSwapChainResources();

    D3D11_VIEWPORT viewport{ };

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = static_cast<Float32>(m_window->GetWidth());
    viewport.Height = static_cast<Float32>(m_window->GetHeight());
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    m_device_context->RSSetViewports(1, &viewport);
    m_device_context->OMSetRenderTargets(1, m_render_target.GetAddressOf(),
                                         nullptr);
  }

  void D3D11Context::SwapBuffers()
  {
    // TODO: Move buffer clear color somewhere else.

    constexpr Float32 clear_color[]{ 0.41f, 0.41f, 0.67f, 1.0f };

    m_device_context->ClearRenderTargetView(m_render_target.Get(), clear_color);

    m_swap_chain->Present(1, 0);
  }

  void D3D11Context::CreateSwapChainResources()
  {
    ComPtr<ID3D11Texture2D> back_buffer{ nullptr };

    if (FAILED(m_swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer))))
    {
      CORVUS_LOG_FATAL("Failed to get the back buffer from swap chain");

      return;
    }

    if (FAILED(m_device->CreateRenderTargetView(back_buffer.Get(), nullptr,
                                                &m_render_target)))
    {
      CORVUS_LOG_FATAL("Failed to create render target view from back buffer");

      return;
    }
  }

  void D3D11Context::DestroySwapChainResources()
  {
    m_render_target.Reset();
  }
}

#endif
