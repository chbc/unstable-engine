file(GLOB_RECURSE APP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(SampleApplication ${APP_SOURCES})

target_link_libraries(SampleApplication PRIVATE RenderEngine)

target_include_directories(SampleApplication PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    # Pega o diretório base do vcpkg onde as DLLs ficam
    # O comando abaixo copia TUDO que for .dll da pasta bin do vcpkg para a sua pasta bin
    add_custom_command(TARGET SampleApplication POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_FILE_DIR:SDL2::SDL2>/../bin/"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/"
    )
endif()
