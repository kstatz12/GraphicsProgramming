cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.0)

project(app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fdiagnostics-all-candidates -fsanitize=address")
find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
find_package(X11 REQUIRED)
  # note that the order is important for setting the libs
  # use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype ${ASSIMP_LIBRARY})
set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(include)
set(HEADER_FILES include/glad/glad.h include/KHR/khrplatform.h src/renderer.h src/drawable.h src/utils.h src/io.h src/movement.h src/shader.h)

add_library(GLAD "src/glad.c")
set(LIBS ${LIBS} GLAD)

add_executable(app src/glad.c src/main.cpp ${HEADER_FILES})

find_package(glfw3 3.3.10 REQUIRED)
target_link_libraries(app PRIVATE glfw)

set(OpenGL_GL_Preference GLVND)
find_package(OpenGL REQUIRED)
target_link_libraries(app PRIVATE ${OPENGL_gl_LIBRARY})

find_package(glm CONFIG REQUIRED)
target_link_libraries(app PRIVATE glm::glm)

add_custom_command (
  TARGET app POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:app>/shaders
)
