cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

project(UnstableEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} ${CMAKE_BUILD_TYPE})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib)
endforeach()

if (WIN32)
    set(CMAKE_BUILD_TYPE_RELEASE_STR "Release")
    set(CMAKE_MAP_IMPORTED_CONFIG_DEBUG Release)
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

if(WIN32)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_image CONFIG REQUIRED)
else()
    find_package(SDL2 REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
	
	add_library(SDL2_image::SDL2_image ALIAS PkgConfig::SDL2_IMAGE)
endif()

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-DNOMINMAX)
endif()

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
target_include_directories(imguizmo PUBLIC dependencies/imgui)

add_subdirectory(solution/RenderEngine)
add_subdirectory(solution/MeshConverter)
add_subdirectory(solution/SampleApplication)
