cmake_minimum_required(VERSION 3.20)
project(learn)

set(CMAKE_CXX_STANDARD 23)

add_executable(learn
        main.cpp
        utilities.h
        shader.h
        shader.cpp
        )

add_subdirectory(thirdparty/glad/cmake)
add_subdirectory(thirdparty/glfw)

glad_add_library(glad_lib STATIC API gl:core=3.3)
target_link_libraries(learn glfw glad_lib ${OPENGL_LIBRARY})