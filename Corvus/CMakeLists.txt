cmake_minimum_required(VERSION 3.30...3.80)
project(Corvus)

add_library(Corvus SHARED
  "include/Corvus/Engine.hpp"
  "include/Corvus/Entry.hpp"
  "source/Core/Core.hpp"
  "source/Platform/D3D11Context.hpp"
  "source/Platform/D3D11Context.cpp"
  "source/Platform/Platform.hpp"
  "source/Platform/Platform.cpp"
  "source/Platform/Win32EventPoll.hpp"
  "source/Platform/Win32EventPoll.cpp"
  "source/Platform/Win32Window.hpp"
  "source/Platform/Win32Window.cpp"
  "source/Application.hpp"
  "source/Application.cpp"
  "source/Event.hpp"
  "source/Event.cpp"
  "source/GraphicsContext.hpp"
  "source/GraphicsContext.cpp"
  "source/Layer.hpp"
  "source/Layer.cpp"
  "source/Log.hpp"
  "source/Log.cpp"
  "source/Window.hpp"
  "source/Window.cpp"
)

target_compile_definitions(Corvus
  PUBLIC
  $<$<CONFIG:Debug>:"CORVUS_DEBUG">
  PRIVATE
  "CORVUS_BUILD_ENGINE"
)

target_precompile_headers(Corvus
  PRIVATE
  "source/Core/PCH.hpp"
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
      dxgi d3d11
    )
  endif()

  target_compile_definitions(Corvus
    PUBLIC
    "UNICODE"
    "_UNICODE"
    "CORVUS_PLATFORM_WIN32"
  )
endif()
