#pragma once

#include <string>

namespace Utils
{

void renderSphere();
void renderCube();
void renderQuad();
unsigned int loadTexture(const char* path);
unsigned int loadHdrTexture(const char* path);
void saveHdrTexture(int width, int height, const std::string& filePath, float* data);
uint32_t createShader(const std::string& vertexFile, const std::string& fragmentFile);
void checkCompileErrors(uint32_t shader, uint32_t mode);
void checkProgramLink(uint32_t program);

} // namespace
