#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>
#include <memory>
#include <variant>

#include "utils.h"

namespace Shaders {
class Compiler {
private:
public:
  static Util::Result<unsigned long, std::string> compile(unsigned int, unsigned int, std::unique_ptr<char[]>);
};
} // namespace Shaders

class Texture {

};


struct ShaderRegistryEntry {
    unsigned int ShaderId;
    unsigned int ShaderType;
};

class Registry {
private:
    unsigned int shaderProgramId;
public:

    void draw();
}


#endif // SHADER_H_
