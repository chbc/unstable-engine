set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/tools")

file(GLOB_RECURSE APP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(MeshConverter ${APP_SOURCES})

target_link_libraries(MeshConverter PUBLIC	
	RenderEngine
	ryml::ryml
)

target_include_directories(MeshConverter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

