file(GLOB_RECURSE ENGINE_SOURCES
    "src/*.cpp"
    "include/*.h"
    "thirdParties/*.h"
    "thirdParties/*.cpp"
)

set(CMAKE_CXX_STANDARD 17)

add_library(RenderEngine ${ENGINE_SOURCES})

target_compile_definitions(RenderEngine PUBLIC
    RYML_STATIC_DEFINE
    C4CORE_WITH_STD_STRING
)

target_include_directories(RenderEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdParties
)

target_link_libraries(RenderEngine PUBLIC
    OpenGL::GL
    SDL2::SDL2
    PkgConfig::SDL2_IMAGE
    GLEW::GLEW
    assimp::assimp
    ryml::ryml
    c4core::c4core
    imgui
    imguizmo
    glm
)
