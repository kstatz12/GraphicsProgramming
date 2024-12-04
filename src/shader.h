#ifndef SHADER_H_
#define SHADER_H_

#include <cmath>
#include <glad/glad.h>
#include <memory>
#include "io.h"
#include "utils.h"
#include <glm/glm.hpp>
#include <stdexcept>

class Shader {
private:
  unsigned int programId;
  Shader(std::unique_ptr<const char[]> vertexContent,
         std::unique_ptr<const char[]> fragmentContent) {

    unsigned int vertex, fragment;

    // just get the raw pointer here because its what GLFW speaks
    // silly c
    vertex = compile_shader(vertexContent.get(), GL_VERTEX_SHADER);
    fragment = compile_shader(fragmentContent.get(), GL_FRAGMENT_SHADER);

    this->programId = glCreateProgram();

    glAttachShader(programId, vertex);
    glAttachShader(programId, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  GLint compile_shader(const char *code, const GLint type) {
    if (code == nullptr) {
      throw std::runtime_error("Shader source code is null.");
    }

    // Create the shader object
    GLint shaderId = glCreateShader(type);
    if (shaderId == 0) {
      throw std::runtime_error("Failed to create shader object.");
    }

    // Attach the source code to the shader
    glShaderSource(shaderId, 1, &code, nullptr);

    // Compile the shader
    glCompileShader(shaderId);

    // Check for compilation success
    GLint compileStatus = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
      // Retrieve and log the error message
      GLint logLength = 0;
      glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

      std::string errorMessage;
      if (logLength > 0) {
        std::string log(logLength, '\0');
        glGetShaderInfoLog(shaderId, logLength, nullptr, log.data());
        errorMessage = "Shader compilation failed: " + log;
      } else {
        errorMessage = "Shader compilation failed with no log.";
      }

      // Clean up shader object
      glDeleteShader(shaderId);
      throw std::runtime_error(errorMessage);
    }

    return shaderId;
  }

public:
  static std::unique_ptr<Shader> InlineShader(const char *vertexContent,
                                              const char *fragmentContent) {
    return std::unique_ptr<Shader>(
        new Shader(std::unique_ptr<const char[]>(vertexContent),
                   std::unique_ptr<const char[]>(fragmentContent)));
  }
  static std::unique_ptr<Shader> FileShader(const char *vertexPath,
                                            const char *fragmentPath) {
    auto vertexContents = IO::File::getContents(vertexPath);
    auto fragmentContents = IO::File::getContents(fragmentPath);

    if (vertexContents.isOk() && fragmentContents.isOk()) {
      return std::unique_ptr<Shader>(
          new Shader(std::move(vertexContents.unwrap()),
                     std::move(fragmentContents.unwrap())));
    } else {
      return nullptr;
    }
  }

  void activate() { glUseProgram(programId); }

  void setMatrix4(const char *name, const glm::mat4 &mat, bool activate) {
    if (activate)
      this->activate();
    glUniformMatrix4fv(glGetUniformLocation(programId, name), 1, GL_FALSE,
                       &mat[0][0]);
  }

  void setVector3f(const char *name, const glm::vec3 &value,
                   const bool activate) {
    if (activate)
      this->activate();
    glUniform3f(glGetUniformLocation(this->programId, name), value.x, value.y,
                value.z);
  }
};

#endif // SHADER_H_
