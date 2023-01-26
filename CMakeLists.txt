cmake_minimum_required(VERSION 3.20)
project(OpenGL_learn)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glfw)
add_executable(OpenGL_learn main.cpp)
target_link_libraries(OpenGL_learn glfw ${OPENGL_LIBRARY})