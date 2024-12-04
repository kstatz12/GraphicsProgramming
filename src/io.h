#ifndef IO_H_
#define IO_H_

#include "utils.h"
#include <fstream>
#include <memory>

namespace IO {
class File {
public:
  static Util::Result<std::unique_ptr<char[]>, std::string>
  getContents(const char *path) {
    std::ifstream file(path);

    if (!file.is_open()) {
      return Util::Result<std::unique_ptr<char[]>, std::string>::Err(
          "Could Not Open File");
    }
    try {
      std::streampos size = file.tellg();

      std::unique_ptr<char[]> fileContents =
          std::make_unique<char[]>((ulong)size + 1);

      file.seekg(0, std::ios::beg);
      file.read(fileContents.get(), size);

      fileContents[size] = '\0';

      file.close();

      return Util::Result<std::unique_ptr<char[]>, std::string>::Ok(
          std::move(fileContents));

    } catch (...) {
      return Util::Result<std::unique_ptr<char[]>, std::string>::Err(
          "Cannot Read File Contents");
    }
  }
};
} // namespace IO

#endif // IO_H_
