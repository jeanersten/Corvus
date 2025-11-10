cmake_minimum_required(VERSION 3.30...3.80)
project(Corvus)

add_executable(Sandbox
  "source/Sandbox.cpp"
)

if(WIN32)
  set_target_properties(Sandbox
    PROPERTIES
    WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>
  )
endif()
