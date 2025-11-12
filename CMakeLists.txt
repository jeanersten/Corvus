cmake_minimum_required(VERSION 3.30...3.80)
project(Corvus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory("Corvus")
add_subdirectory("Sandbox")

target_link_libraries(Sandbox PRIVATE Corvus)

set_target_properties(Sandbox
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib"
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin"
)

set_target_properties(Corvus
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib"
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin"
)

if(WIN32)
  set_property(
    DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY
    VS_STARTUP_PROJECT Sandbox
  )
endif()
