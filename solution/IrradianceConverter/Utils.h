#pragma once

#include <string>

namespace Utils
{

uint32_t createShader(const std::string& vertexFile, const std::string& fragmentFile);
void checkCompileErrors(uint32_t shader, uint32_t mode);
void checkProgramLink(uint32_t program);

} // namespace
