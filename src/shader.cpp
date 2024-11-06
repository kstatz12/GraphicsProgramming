#include "shader.h"
#include "utils.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Util::Result<unsigned long, std::string>Shaders::Compiler::compile(unsigned int shaderProgramId, unsigned int shaderType, std::unique_ptr<char[]> contents)
{
    unsigned int shader = glCreateShader(shaderType);
    const char * ptr = contents.get();

    glShaderSource(shader, 1, &ptr, NULL);
    glCompileShader(shader);

    return Util::Result<unsigned long, std::string>::Ok(std::move(shader));
}
