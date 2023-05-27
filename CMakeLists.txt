cmake_minimum_required(VERSION 3.20)
project(learn)

set(CMAKE_CXX_STANDARD 23)

add_executable(learn
        src/main.cpp
        src/utilities.h
        src/shader.h
        src/shader.cpp
        src/vertex_buffer.h
        src/vertex_buffer.cpp
        src/vertex_buffer_layout.h
        src/vertex_buffer_layout.cpp
        src/vertex_array.h
        src/vertex_array.cpp
        src/index_buffer.h
        src/index_buffer.cpp
        src/renderer.h
        src/renderer.cpp
        )

add_subdirectory(thirdparty/glad/cmake)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)

#find_package(Boost REQUIRED COMPONENTS filesystem)
#target_include_directories(learn PUBLIC ${BOOST_INCLUDE_DIR})

glad_add_library(glad_lib STATIC API gl:core=3.3)
target_link_libraries(learn glfw glad_lib ${OPENGL_LIBRARY} glm::glm)