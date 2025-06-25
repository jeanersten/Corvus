cmake_minimum_required (VERSION 3.10)

project (Corvus LANGUAGES CXX)

add_subdirectory ("vendor/glad-02.00")
add_subdirectory ("vendor/glfw-03.04")
add_subdirectory ("vendor/spdlog-01.15")

add_definitions (-DGLFW_BUILD_NONE)

add_executable (Corvus 
  "source/Main.cpp"
)

target_link_libraries (Corvus PRIVATE glad glfw spdlog::spdlog)
