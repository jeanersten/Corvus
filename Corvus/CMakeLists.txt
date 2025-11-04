cmake_minimum_required(VERSION 3.30...3.80)
project(Corvus LANGUAGES C CXX)

add_library(Corvus SHARED
  "include/Corvus/Engine.hpp"
  "source/Core/Core.hpp"
  "source/Application.hpp"
  "source/Application.cpp"
  "source/Event.hpp"
  "source/Event.cpp"
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
  target_compile_definitions(Corvus
    PUBLIC
    "UNICODE"
    "_UNICODE"
    "CORVUS_PLATFORM_WIN32"
  )
endif()
