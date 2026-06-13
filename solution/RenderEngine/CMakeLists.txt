file(GLOB_RECURSE ENGINE_SOURCES "*.cpp" "*.h")

set(CMAKE_CXX_STANDARD 17)

add_library(RenderEngine ${ENGINE_SOURCES})

target_include_directories(RenderEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdParties
)

target_link_libraries(RenderEngine PUBLIC SDL2::SDL2 GLEW::GLEW assimp::assimp)
target_link_libraries(RenderEngine PRIVATE PkgConfig::SDL2_IMAGE)

target_link_libraries(RenderEngine
    PUBLIC
    ryml
    c4core
    imgui
    imguizmo
    glm
)
