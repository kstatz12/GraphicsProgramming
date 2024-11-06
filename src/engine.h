#ifndef ENGINE_H_
#define ENGINE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <memory>

struct EngineConfig {
  unsigned int height;
  unsigned int width;
  unsigned int glfwMajorVersion;
  unsigned int glfwMinorVersion;
  unsigned int glfwProfile;
  char *windowName;
};

struct EngineContext {
  unsigned int ID;
  GLFWwindow *window;
};

class Engine {
private:
  EngineConfig config;
  EngineContext *engineContext;

public:
  Engine(EngineConfig config);
  ~Engine();
  void init();
  void draw(std::function<void(EngineContext)> func);
};

class EnginePlugin {
public:
  virtual void run() {};

  virtual ~EnginePlugin() {}
};

struct ShaderPluginConfig {
  char *vertexPath;
  char *fragmentPath;
};

class ShaderPlugin : public EnginePlugin {
private:
  ShaderPluginConfig config;

public:
  ShaderPlugin(ShaderPluginConfig config);
  void run() override;
};

#endif // ENGINE_H_
