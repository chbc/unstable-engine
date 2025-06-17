#include "DebugRenderer.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "CameraComponent.h"

namespace sre
{

DebugRenderer::DebugRenderer(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper)
	: shaderManager(shaderManager), graphicsWrapper(graphicsWrapper)
{ }

DebugRenderer::~DebugRenderer()
{
	if (this->shaderManager != nullptr)
	{
		this->shaderManager->releaseShader(this->program);
	}
}

void DebugRenderer::addBox(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
{
	std::vector<glm::vec3> vertices;
	std::vector<uint32_t> indices;

	glm::vec3 halfSize = size * 0.5f;

    std::vector<glm::vec3> verticesData =
    {
        {-halfSize.x, -halfSize.y,  halfSize.z},
		{ halfSize.x, -halfSize.y,  halfSize.z},
		{ halfSize.x,  halfSize.y,  halfSize.z},
        {-halfSize.x,  halfSize.y,  halfSize.z},

        {-halfSize.x, -halfSize.y, -halfSize.z},
        { halfSize.x, -halfSize.y, -halfSize.z},
        { halfSize.x,  halfSize.y, -halfSize.z},
        {-halfSize.x,  halfSize.y, -halfSize.z}
    };

    std::vector<unsigned int> indicesData =
    {
        0, 1, 1, 2, 2, 3, 3, 0, // Front
        4, 5, 5, 6, 6, 7, 7, 4, // Back
        0, 4, 1, 5, 2, 6, 3, 7
    };

	for (const glm::vec3& item : verticesData)
	{
		vertices.push_back(position + item);
	}

	for (const unsigned int& item : indicesData)
	{
		indices.push_back(item);
	}

	ColorMeshData* meshData = new ColorMeshData{ "DebugBox", vertices, indices, color };
	this->graphicsWrapper->createBuffers(meshData);
	this->meshes.emplace_back(meshData);
}

void DebugRenderer::loadShader()
{
    this->program = this->shaderManager->loadDebugShader();
    this->shaderManager->setupAttributeLocation(this->program, ShaderVariables::IN_POSITION);
    this->shaderManager->setupUniformLocation(this->program, ShaderVariables::VIEW_MATRIX);
    this->shaderManager->setupUniformLocation(this->program, ShaderVariables::PROJECTION_MATRIX);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::MATERIAL_COLOR);
}

void DebugRenderer::render(CameraComponent* camera)
{
    const glm::mat4& viewMatrix = camera->getViewMatrix();
    const glm::mat4& projectionMatrix = camera->getProjectionMatrix();

	this->shaderManager->enableShader(this->program);

    this->shaderManager->setMat4(this->program, ShaderVariables::VIEW_MATRIX, &viewMatrix[0][0]);
	this->shaderManager->setMat4(this->program, ShaderVariables::PROJECTION_MATRIX, &projectionMatrix[0][0]);

	for (const UPTR<ColorMeshData>& item : this->meshes)
	{
        this->graphicsWrapper->bindVAO(item->vao, item->vbo);
        this->graphicsWrapper->enableColorMeshSettings();

		this->shaderManager->setVec4(this->program, ShaderVariables::MATERIAL_COLOR, &item->color[0]);
		this->graphicsWrapper->drawElement(item->ebo, item->indices.size(), EDrawMode::LINES);

		this->graphicsWrapper->disableColorMeshSettings();
	}
}

} // namespace
