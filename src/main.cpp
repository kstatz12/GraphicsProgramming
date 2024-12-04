#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include "drawable.h"
#include "shader.h"
#include "renderer.h"
#include "engine.h"

#define SCR_WIDTH 800
#define SCR_HEIGHT 800

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 transform;"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos, 1.0); "
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main() {
  Engine e;

  std::unique_ptr<Renderer> r = Renderer::from_shader([]() {
    return Shader::InlineShader(vertexShaderSource, fragmentShaderSource);
  });

  auto drawable = DrawableBuilder()
    .setRotation(0.0f)
    .setColor({ 1.0f, 1.0f, 1.0f })
    .setPosition({ 0.0f, 0.0f })
    .build();


  e.on_update([&](auto window) {
    // process_input(window);
    r->render(drawable);
    glfwSwapBuffers(window);
    glfwPollEvents();
  });
}
