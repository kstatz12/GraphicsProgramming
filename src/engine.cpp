#include "engine.h"
#include "io.h"

#include "shader.h"
#include <stdexcept>

Engine::Engine(EngineConfig config) { this->config = config; }

Engine::~Engine() {
  glfwTerminate();
  delete this->engineContext;
}

void Engine::init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->config.glfwMajorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->config.glfwMinorVersion);
  glfwWindowHint(GLFW_OPENGL_PROFILE, this->config.glfwProfile);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(this->config.width, this->config.height,
                                        this->config.windowName, NULL, NULL);
  if (window == NULL) {
    throw std::runtime_error("Failed To Creat GLFW Window");
  }

  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow *window, int width, int height) -> void {
        glViewport(0, 0, width, height);
      });

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      throw std::runtime_error("Failed To Initialize GLAD");
  }

  unsigned int shaderProgram = glCreateProgram();

  this->engineContext = new EngineContext();
  engineContext->window = window;
  engineContext->ID = shaderProgram;
}


ShaderPlugin::ShaderPlugin(ShaderPluginConfig config)
{

}
