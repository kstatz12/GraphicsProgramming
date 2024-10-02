cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.0)

project(graphics_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

link_directories(${CMAKE_SOURCE_DIR/lib})


add_executable(app src/main.cpp)

find_package(glfw3 3.3.10 REQUIRED)

target_link_libraries(app glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(app ${OPENGL_gl_LIBRARY})

add_library(GLAD "src/glad.c")
set(LIBS ${LIBS} GLAD)

include_directories(${CMAKE_SOURCE_DIR}/include)
