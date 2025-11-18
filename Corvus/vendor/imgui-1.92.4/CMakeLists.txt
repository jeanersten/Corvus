cmake_minimum_required(VERSION 3.30)
project(imgui)

add_library(imgui STATIC
  "include/imgui/imgui.h"
  "source/imgui_impl_dx11.h"
  "source/imgui_impl_dx11.cpp"
  "source/imgui_impl_opengl3.h"
  "source/imgui_impl_opengl3_loader.h"
  "source/imgui_impl_opengl3.cpp"
  "source/imgui_impl_win32.h"
  "source/imgui_impl_win32.cpp"
  "source/imconfig.h"
  "source/imgui.cpp"
  "source/imgui_demo.cpp"
  "source/imgui_draw.cpp"
  "source/imgui_internal.h"
  "source/imgui_tables.cpp"
  "source/imgui_widgets.cpp"
  "source/imstb_rectpack.h"
  "source/imstb_textedit.h"
  "source/imstb_truetype.h"
)

target_include_directories(imgui
  PUBLIC
  "include"
  PRIVATE
  "source"
)
