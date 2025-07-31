cmake_minimum_required (VERSION 3.20...3.30)

project (Corvus)


add_library (Corvus SHARED
  "Include/Corvus/Engine.hpp"

  "Source/Core/Core.hpp"
  "Source/Core/Types.hpp"

  "Source/Window/Win32/Win32Window.cpp"
  "Source/Window/Win32/Win32Window.hpp"
  "Source/Window/Window.cpp"
  "Source/Window/Window.hpp"
)

target_include_directories (Corvus PUBLIC "Include")


set_target_properties (Corvus
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/$<CONFIG>/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/$<CONFIG>/bin"
)


target_compile_definitions (Corvus
  PUBLIC
  $<$<CONFIG:Debug>:CORVUS_DEBUG>
  $<$<CONFIG:Release>:CORVUS_RELEASE>
  PRIVATE
  CORVUS_BUILD_DLL
)


if (WIN32)

target_compile_definitions (Corvus
  PUBLIC
  CORVUS_PLATFORM_WIN32
)

endif ()
