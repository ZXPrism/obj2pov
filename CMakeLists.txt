cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(obj2pov LANGUAGES CXX)

file(GLOB_RECURSE PROJ_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.cpp)

add_library(obj2pov ${PROJ_SOURCES})
target_include_directories(obj2pov PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test PUBLIC obj2pov)

add_custom_command(TARGET test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:test>
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/obj2pov.exe
)

add_custom_command(TARGET test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/test/teapot.obj
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/teapot.obj
)
