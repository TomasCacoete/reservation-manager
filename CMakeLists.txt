cmake_minimum_required(VERSION 3.5)
project(reservation_manager)

file(GLOB SOURCES src/*.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(main ${SOURCES})

target_compile_options(main PRIVATE -g)

add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)