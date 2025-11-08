cmake_minimum_required(VERSION 3.30...3.80)
project(Corvus LANGUAGES C CXX)

add_library(Corvus SHARED
  "include/Corvus/Engine.hpp"
  "source/Core/Core.hpp"
  "source/Application.hpp"
  "source/Application.cpp"
  "source/D3D11Context.hpp"
  "source/D3D11Context.cpp"
  "source/Event.hpp"
  "source/Event.cpp"
  "source/GraphicsContext.hpp"
  "source/GraphicsContext.cpp"
  "source/Layer.hpp"
  "source/Layer.cpp"
  "source/Log.hpp"
  "source/Log.cpp"
  "source/Platform.hpp"
  "source/Platform.cpp"
  "source/Win32Window.hpp"
  "source/Win32Window.cpp"
  "source/Window.hpp"
  "source/Window.cpp"
)

target_compile_definitions(Corvus
  PUBLIC
  $<$<CONFIG:Debug>:"CORVUS_DEBUG">
  $<$<CONFIG:Release>:"CORVUS_RELEASE">
  PRIVATE
  "CORVUS_BUILD_ENGINE"
)

target_include_directories(Corvus PUBLIC "include")

if(WIN32)
  option(CORVUS_USE_DIRECT3D11_RENDERER "Use Direct3D 11 for rendering" OFF)

  if(CORVUS_USE_DIRECT3D11_RENDERER)
    target_compile_definitions(Corvus
      PUBLIC
      "CORVUS_RENDERER_DIRECT3D11"
    )

    target_link_libraries(Corvus
      d3d11 dxgi
    )
  endif()

  target_compile_definitions(Corvus
    PUBLIC
    "UNICODE"
    "_UNICODE"
    "CORVUS_PLATFORM_WIN32"
  )
endif()
