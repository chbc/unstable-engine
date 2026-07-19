file(GLOB_RECURSE ENGINE_SOURCES
    "src/*.cpp"
    "include/*.h"
    "thirdParties/*.h"
    "thirdParties/*.cpp"
)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    add_library(RenderEngine SHARED ${ENGINE_SOURCES})
    target_compile_definitions(RenderEngine PRIVATE SRE_DLL_EXPORT)
else()
    add_library(RenderEngine ${ENGINE_SOURCES})
endif()

target_include_directories(RenderEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdParties
)

target_link_libraries(RenderEngine PUBLIC
    OpenGL::GL
    SDL2::SDL2
    SDL2_image::SDL2_image
    GLEW::GLEW
    assimp::assimp
    ryml::ryml
    imgui
    imguizmo
    glm
)
