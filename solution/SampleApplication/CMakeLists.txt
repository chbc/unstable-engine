file(GLOB_RECURSE APP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(SampleApplication ${APP_SOURCES})

target_link_libraries(SampleApplication PRIVATE RenderEngine)

target_include_directories(SampleApplication PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
