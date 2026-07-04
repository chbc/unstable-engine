cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

project(UnstableEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Encontrar dependências globais
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)

set(RYML_WITH_STD_STRING ON CACHE BOOL "Build ryml with std::string support" FORCE)
set(C4CORE_WITH_STD_STRING ON CACHE BOOL "Build c4core with std::string support" FORCE)

add_subdirectory(dependencies/rapidyaml)
add_subdirectory(dependencies/glm)

# imgui
add_library(imgui STATIC
dependencies/imgui/imgui.cpp
dependencies/imgui/imgui_draw.cpp
dependencies/imgui/imgui_tables.cpp
dependencies/imgui/imgui_widgets.cpp
dependencies/imgui/imgui_demo.cpp
dependencies/imgui/backends/imgui_impl_opengl3.cpp
dependencies/imgui/backends/imgui_impl_sdl2.cpp
dependencies/imgui/misc/cpp/imgui_stdlib.cpp
)

target_include_directories(imgui PUBLIC dependencies/imgui)

target_link_libraries(imgui PUBLIC
    SDL2::SDL2
    OpenGL::GL
)

add_subdirectory(dependencies/imguizmo)

add_subdirectory(solution/RenderEngine)
add_subdirectory(solution/SampleApplication)
