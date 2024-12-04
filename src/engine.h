#ifndef ENGINE_H_
#define ENGINE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "drawable.h"

#include <memory>
#include <vector>
#include <string>
#include <functional>

struct Engine {
private:
  GLFWwindow *window;
  std::vector<std::shared_ptr<Drawable>> drawables;

  GLFWwindow *init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->glfwMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->glfwMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, this->glfwProfile);

    GLFWwindow *window = glfwCreateWindow(
        this->width, this->height, this->windowName.c_str(), nullptr, nullptr);
    if (!window) {
      glfwTerminate(); // Clean up GLFW resources
      throw std::runtime_error("Failed to create GLFW window");
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      throw std::runtime_error("Failed to Load Glad");
    }

    // Set the framebuffer size callback
    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow *win, int w, int h) { glViewport(0, 0, w, h); });
    return window;
  }

public:
  unsigned int height;
  unsigned int width;
  unsigned int glfwMajorVersion;
  unsigned int glfwMinorVersion;
  unsigned int glfwProfile;
  std::string windowName;

  Engine() {
    height = 600;
    width = 800;
    glfwMajorVersion = 3;
    glfwMinorVersion = 3;
    glfwProfile = GLFW_OPENGL_CORE_PROFILE;
    windowName = "Hello Games";

    this->window = init();
  }

  void register_drawable(std::function<void(DrawableBuilder &)> fn) {
    auto db = DrawableBuilder();
    fn(db);
    this->drawables.push_back(db.build());
  }

  void on_update(std::function<void(GLFWwindow *)> f) {
    while (!glfwWindowShouldClose(this->window)) {
      f(this->window);
    }
  }

  ~Engine() { glfwTerminate(); }
};

#endif // ENGINE_H_
