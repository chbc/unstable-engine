#include "Utils.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <fstream>
#include <sstream>

namespace Utils
{

uint32_t createShader(const std::string& vertexFile, const std::string& fragmentFile)
{
	std::ifstream vertexStream(vertexFile);
	std::ifstream fragmentStream(fragmentFile);
	
	if (!vertexStream.is_open())
		throw "[Utils] Can't open vertex shader file: " + vertexFile;
	if (!fragmentStream.is_open())
		throw "[Utils] Can't open fragment shader file: " + fragmentFile;

	std::stringstream vertexBuffer;
	std::stringstream fragmentBuffer;

	vertexBuffer << vertexStream.rdbuf();
	fragmentBuffer << fragmentStream.rdbuf();

	vertexStream.close();
	fragmentStream.close();

	std::string vertexBufferStr = vertexBuffer.str();
	std::string fragmentBufferStr = fragmentBuffer.str();

	const char* vertexContent = vertexBufferStr.c_str();
	const char* fragmentContent = fragmentBufferStr.c_str();

	// Create shaders
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexContent, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, GL_VERTEX_SHADER);

	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentContent, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, GL_FRAGMENT_SHADER);

	uint32_t program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	checkProgramLink(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

void checkCompileErrors(uint32_t shader, uint32_t mode)
{
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		char error[1024];
		glGetShaderInfoLog(shader, 1000, NULL, error);

		std::string shaderType = "UNKNOWN";
		switch (mode)
		{
			case GL_VERTEX_SHADER:      shaderType = "VERTEX_SHADER"; break;
			case GL_FRAGMENT_SHADER:    shaderType = "FRAGMENT_SHADER"; break;
			case GL_GEOMETRY_SHADER:    shaderType = "GEOMETRY_SHADER"; break;
		}

		//= (mode == GL_VERTEX_SHADER) ? "VERTEX SHADER" : "FRAGMENT SHADER";
		throw "[OpenGLAPI] - In shader: " + shaderType + "\n" + error;
	}
}

void checkProgramLink(uint32_t program)
{
	int result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		char error[1024];
		glGetProgramInfoLog(program, 1000, NULL, error);
		glDeleteProgram(program);

		throw "[OpenGLAPI] - In program linking:\n" + std::string(error);
	}
}

} // namespace
