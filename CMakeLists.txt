cmake_minimum_required (VERSION 3.10)

project (Corvus LANGUAGES CXX)

add_subdirectory ("vendor/glad-02.00")
add_subdirectory ("vendor/glfw-03.04")
add_subdirectory ("vendor/spdlog-01.15")

add_definitions (-DGLFW_INCLUDE_NONE)

add_executable (Corvus 
  "source/Game.cpp"
  "source/Init.cpp"
  "source/Log.cpp"
  "source/Main.cpp"
  "source/Window.cpp"

  "source/Game.h"
  "source/Init.h"
  "source/Log.h"
  "source/Window.h"
)

target_link_libraries (Corvus PRIVATE glad glfw spdlog::spdlog)
