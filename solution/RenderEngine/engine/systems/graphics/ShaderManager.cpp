#include <GL/glew.h>

#include "ShaderManager.h"
#include <fstream>
#include <iostream>

namespace graphics
{

IMPLEMENT_SINGLETON(ShaderManager);

ShaderManager::ShaderManager()
{
}

bool ShaderManager::init()
{
	return true;
}

bool ShaderManager::loadFile(std::string fileName, std::string &source)
{
	std::ifstream in(fileName.c_str());

	if (!in.is_open())
	{
		throw "[ShaderManager] - Error: " + fileName + " can't be found!";
	}

	char temp[300];
	while (!in.eof())
	{
		in.getline(temp, 300);
		source += temp;
		source += '\n';
	}

	return true;    // TODO: turn to void
}

unsigned int ShaderManager::compileShader(const std::string &fileName, const std::string &source, unsigned int mode)
{
	unsigned int id = glCreateShader(mode);
	const char *csource = source.c_str();

	glShaderSource(id, 1, &csource, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
    {
        char error[1000];
        glGetShaderInfoLog(id, 1000, NULL, error);

        throw "[ShaderManager] - In file: " + fileName + "\n" + error;
    }

	return id;
}

unsigned int ShaderManager::loadShader(std::string vertexFile, std::string fragmentFile)
{
	std::string source;
	this->loadFile(vertexFile, source);
	unsigned int vertShader = this->compileShader(vertexFile, source, GL_VERTEX_SHADER);

	source = "";

	this->loadFile(fragmentFile, source);
	unsigned int fragShader = this->compileShader(fragmentFile, source, GL_FRAGMENT_SHADER);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);

	glLinkProgram(program);

	this->vertShaders.push(vertShader);
	this->fragShaders.push(fragShader);
	this->programs.push(program);

	return program;
}

// passing values //

void ShaderManager::setValue(unsigned int program, const std::string &varName, float x)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform1f(location, x);
}

void ShaderManager::setValue(unsigned int program, const std::string &varName, float x, float y)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform2f(location, x, y);
}

void ShaderManager::setValue(unsigned int program, const std::string &varName, float x, float y, float z)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform3f(location, x, y, z);
}

void ShaderManager::setValue(unsigned int program, const std::string &varName, float *matrix)
{
    int location = glGetUniformLocation(program, varName.c_str());
    this->checkVariableLocation(location, varName);
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void ShaderManager::setValue(unsigned int program, const std::string &varName, int value)
{
    int location = glGetUniformLocation(program, varName.c_str());
    this->checkVariableLocation(location, varName);
    glUniform1i(location, value);
}

int ShaderManager::getAttribLocation(unsigned int program, EShaderVariable shaderVariable)
{
    int result = -1;
    std::string variable = "INVALID";

    switch (shaderVariable)
    {
        case SHADER_POSITION:   variable = "vertexPosition"; break;
        case SHADER_NORMAL:     variable = "inputNormal"; break;
        default: break;
    }

    result = glGetAttribLocation(program, variable.c_str());
    this->checkVariableLocation(result, variable);

    return result;
}

void ShaderManager::checkVariableLocation(int location, const std::string &varName)
{
    if (location == -1)
        throw ("[ShaderManager] Invalid shader variable: " + varName);
}

// attributes
/*
void ShaderManager::setAttributeValue(const char *idName, float x)
{
	unsigned int location = glGetAttribLocation(this->program, idName);
	glUniform1f(location, x);
}

void ShaderManager::setAttributeValue(const char *idName, float x, float y)
{
	unsigned int location = glGetAttribLocation(this->program, idName);
	glUniform2f(location, x, y);
}

void ShaderManager::setAttributeValue(const char *idName, float x, float y, float z)
{
	unsigned int location = glGetAttribLocation(this->program, idName);
	glUniform3f(location, x, y, z);
}
*/

void ShaderManager::enableShader(unsigned int program)
{
	glUseProgram(program);
}

void ShaderManager::disableShader()
{
	glUseProgram(0);
}

void ShaderManager::release()
{
	unsigned int program = 0;
	unsigned int vertShader = 0;
	unsigned int fragShader = 0;

	while(!this->programs.empty())
	{
		program		= this->programs.top();
		vertShader	= this->vertShaders.top();
		fragShader	= this->fragShaders.top();

		glDetachShader(program, vertShader);
		glDetachShader(program, fragShader);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		glDeleteProgram(program);

		this->programs.pop();
		this->vertShaders.pop();
		this->fragShaders.pop();
	}
}

} // namespace graphics
