#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>

#include <engine/entities/components/meshes/VertexData.h>
#include <engine/utils/memory_aliases.h>

using namespace sre;

/* 
typedef struct
{
  float XYZW[4];
} Vertex;
*/

GLuint
  VertexShaderId,
  FragmentShaderId,
  ProgramId,
  VaoId,
  BufferId,
  IndexBufferId,
  ActiveIndexBuffer = 0;

const GLchar* VertexShader =
{
  "#version 400\n"\

  "layout(location=0) in vec4 in_Position;\n"\
  "layout(location=1) in vec4 in_Color;\n"\
  "out vec4 ex_Color;\n"\

  "void main(void)\n"\
  "{\n"\
  "  gl_Position = in_Position;\n"\
  "  ex_Color = in_Color;\n"\
  "}\n"
};

const GLchar* FragmentShader =
{
  "#version 400\n"\

  "in vec4 ex_Color;\n"\
  "out vec4 out_Color;\n"\

  "void main(void)\n"\
  "{\n"\
  "  out_Color = vec4(1.0, 1.0, 1.0, 1.0); // ex_Color;\n"\
  "}\n"
};

void TEMP_Initialize();
void TEMP_RenderFunction(void);
void TEMP_Cleanup(void);
void TEMP_CreateVBO(void);
void TEMP_DestroyVBO(void);
void TEMP_CreateShaders(void);
void TEMP_DestroyShaders(void);

void TEMP_Initialize()
{
  GLenum GlewInitResult;
  
  glewExperimental = GL_TRUE;
  GlewInitResult = glewInit();

  if (GLEW_OK != GlewInitResult) {
    fprintf(
      stderr,
      "ERROR: %s\n",
      glewGetErrorString(GlewInitResult)
    );
    exit(EXIT_FAILURE);
  }
  
  fprintf(
    stdout,
    "INFO: OpenGL Version: %s\n",
    glGetString(GL_VERSION)
  );

  TEMP_CreateShaders();
  TEMP_CreateVBO();

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void TEMP_RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void TEMP_Cleanup(void)
{
  TEMP_DestroyShaders();
  TEMP_DestroyVBO();
}

void TEMP_CreateVBO(void)
{

	float size = 1.0f;
	float half = size * 0.5f;

	/*
	Vertex Vertices[] =
	{
		{half, half, 0.0f},
		{-half, half, 0.0f},
		{-half,-half, 0.0f},
		{half,-half, 0.0f}
	};
	*/

	/*
	sre::VertexData Vertices[] =
	{
		{{half, half, 0.0f}},
		{{-half, half, 0.0f}},
		{{-half,-half, 0.0f}},
		{{half,-half, 0.0f}}
	};

	GLubyte Indices[] = 
	{
		0, 1, 2,
		2, 3, 0
	};
	*/

	float planeVertices[] = 
	{ 
		half, half, 0,
		-half, half, 0,
		-half,-half, 0,
		half,-half, 0 
	};

	float planeNormals[] = 
	{ 
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1 
	};

	uint32_t planeIndices[] = 
	{ 
		0, 1, 2,
		2, 3, 0 
	};

	sre::VECTOR_UPTR<sre::VertexData> vertexData;
	sre::VertexData *newData;
	for (int i = 0; i < 12; i += 3)
	{
		newData = new sre::VertexData;
		newData->position = glm::vec3(planeVertices[i], planeVertices[i + 1], planeVertices[i + 2]);
		newData->normal = glm::vec3(planeNormals[i], planeNormals[i + 1], planeNormals[i + 2]);
		newData->color = glm::vec3(1.0f, 1.0f, 1.0f);

		vertexData.emplace_back(newData);
	}

	/*
	std::vector<unsigned char> indices;
	for (int i = 0; i < 6; i++)
		indices.push_back(planeIndices[i]);
		*/

	/*
  GLenum ErrorCheckValue = glGetError();
  const size_t BufferSize = sizeof(Vertices);
  const size_t VertexSize = sizeof(Vertices[0]);
  */
  // const size_t RgbOffset = sizeof(Vertices[0].XYZW);
  
  // glGenVertexArrays(1, &VaoId);
  // glBindVertexArray(VaoId);
  
	int ttSize = vertexData.size();
	VertexData *vertexDataArray = new VertexData[ttSize];
	for (int i = 0; i < ttSize; i++)
		vertexDataArray[i] = *vertexData[i].get();	// ###

  glGenBuffers(1, &BufferId);
  glBindBuffer(GL_ARRAY_BUFFER, BufferId);
  glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(VertexData), vertexDataArray, GL_STATIC_DRAW);

  delete[] vertexDataArray;

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
  // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

  glEnableVertexAttribArray(0);
  // glEnableVertexAttribArray(1);

  glGenBuffers(1, &IndexBufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);

  GLint ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    fprintf(
      stderr,
      "ERROR: Could not create a VBO: %s \n",
		"###"
    );

    exit(-1);
  }
}

void TEMP_DestroyVBO(void)
{
  GLenum ErrorCheckValue = glGetError();

  // glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &BufferId);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &IndexBufferId);

  // glBindVertexArray(0);
  // glDeleteVertexArrays(1, &VaoId);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    fprintf(
      stderr,
      "ERROR: Could not destroy the VBO: %s \n",
		"###"
    );

    exit(-1);
  }
}

void TEMP_CreateShaders(void)
{
  GLenum ErrorCheckValue = glGetError();
  
  VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
  glCompileShader(VertexShaderId);

  FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
  glCompileShader(FragmentShaderId);

  ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
  glLinkProgram(ProgramId);
  glUseProgram(ProgramId);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    fprintf(
      stderr,
      "ERROR: Could not create the shaders: %s \n",
      "###"
    );

    exit(-1);
  }
}

void TEMP_DestroyShaders(void)
{
  GLenum ErrorCheckValue = glGetError();

  glUseProgram(0);

  glDetachShader(ProgramId, VertexShaderId);
  glDetachShader(ProgramId, FragmentShaderId);

  glDeleteShader(FragmentShaderId);
  glDeleteShader(VertexShaderId);

  glDeleteProgram(ProgramId);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    fprintf(
      stderr,
      "ERROR: Could not destroy the shaders: %s \n",
      "###"
    );

    exit(-1);
  }
}
