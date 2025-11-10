#pragma once

#if defined(CORVUS_PLATFORM_WIN32)
  #include <windows.h>
  #include <wrl.h>

  #if defined(CORVUS_RENDERER_DIRECT3D11)
    #include <dxgi.h>
    #include <d3d11.h>
  #endif
#endif

#include <algorithm>
#include <chrono>
#include <cwchar>
#include <format>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <thread>
