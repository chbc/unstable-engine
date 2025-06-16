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
	this->shaderManager->releaseShader(this->shader);
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
        0, 1, 2,    2, 3, 0, // front
		4, 5, 6,	6, 7, 4, // back
		3, 2, 6,    6, 7, 3, // top
		0, 4, 5,    5, 1, 0, // bottom
        1, 5, 6,    6, 2, 1, // right
        4, 0, 3,    3, 7, 4  // left
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
	this->meshes.emplace_back(meshData);

	this->graphicsWrapper->createBuffers(meshData);
}

void DebugRenderer::loadShader()
{
    this->shader = this->shaderManager->loadDebugShader();
    this->shaderManager->setupAttributeLocation(this->shader, ShaderVariables::IN_POSITION);
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::VIEW_MATRIX);
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::PROJECTION_MATRIX);
}

void DebugRenderer::render(CameraComponent* camera)
{
    const glm::mat4& viewMatrix = camera->getViewMatrix();
    const glm::mat4& projectionMatrix = camera->getProjectionMatrix();

    this->shaderManager->setMat4(shader, ShaderVariables::VIEW_MATRIX, &viewMatrix[0][0]);
    this->shaderManager->setMat4(shader, ShaderVariables::PROJECTION_MATRIX, &projectionMatrix[0][0]);

	for (const UPTR<ColorMeshData>& item : this->meshes)
	{
        this->graphicsWrapper->bindVAO(item->vao, item->vbo);
        this->graphicsWrapper->enableColorMeshSettings();

		this->graphicsWrapper->drawElement(item->ebo, item->indices.size(), EDrawMode::LINES);

		this->graphicsWrapper->disableColorMeshSettings();
	}
}

} // namespace
