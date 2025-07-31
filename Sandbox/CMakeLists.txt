cmake_minimum_required (VERSION 3.20...3.30)

project (Corvus)


add_executable (Sandbox
  "Source/Sandbox.cpp"
)

target_link_libraries (Sandbox PRIVATE Corvus)


set_target_properties (Sandbox
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/$<CONFIG>/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/$<CONFIG>/bin"
)
