#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>
#include <memory>

#include "utils.h"

namespace Shaders {
class Compiler {
private:
public:
  static Util::Result<unsigned long, std::string> compile(unsigned int, std::unique_ptr<char[]>);
};
} // namespace Shaders
#endif // SHADER_H_
