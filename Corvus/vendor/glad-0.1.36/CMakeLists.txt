cmake_minimum_required(VERSION 3.30)
project(glad)

add_library(glad STATIC
  "include/glad/glad.h"
  "include/KHR/khrplatform.h"
  "source/glad.c"
)

target_include_directories(glad PUBLIC "include")
