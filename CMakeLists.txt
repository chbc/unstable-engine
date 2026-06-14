cmake_minimum_required(VERSION 3.10)
project(UnstableEngine)

set(CMAKE_CXX_STANDARD 17)

# Encontrar dependências globais
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)

add_subdirectory(dependencies/rapidyaml)
add_subdirectory(dependencies/glm)

# imgui
add_library(imgui STATIC
dependencies/imgui/imgui.cpp
dependencies/imgui/imgui_draw.cpp
dependencies/imgui/imgui_tables.cpp
dependencies/imgui/imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC dependencies/imgui)

add_subdirectory(dependencies/imguizmo)

add_subdirectory(solution/RenderEngine)
