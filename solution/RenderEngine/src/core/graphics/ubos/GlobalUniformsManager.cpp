#include "GlobalUniformsManager.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "UniformBuffer.h"
#include "LightsUBO.h"
#include "CameraUBO.h"

namespace sre
{

struct GlobalUniformsManager::BuffersImpl
{
	UniformBuffer<LightsUBO> lights{ 0 };
	UniformBuffer<CameraUBO> camera{ 1, true };
};

GlobalUniformsManager::GlobalUniformsManager() = default;

GlobalUniformsManager::~GlobalUniformsManager() = default;

void GlobalUniformsManager::init()
{
	this->buffersImpl = UPTR<BuffersImpl>(new BuffersImpl());
	this->graphicsWrapper = SingletonsManager::Get<AGraphicsWrapper>();
}

void GlobalUniformsManager::release()
{
	if (this->buffersImpl->lights.id != 0)
	{
		this->graphicsWrapper->deleteUniformBuffer(this->buffersImpl->lights.id);
	}

	if (this->buffersImpl->camera.id != 0)
	{
		this->graphicsWrapper->deleteUniformBuffer(this->buffersImpl->camera.id);
	}
}

void GlobalUniformsManager::update()
{
	UniformBuffer<LightsUBO>& lights = this->buffersImpl->lights;
	UniformBuffer<CameraUBO>& camera = this->buffersImpl->camera;

	this->updateBuffer(lights.bindingPoint, lights.isDirty(), lights.id, sizeof(LightsUBO), &lights.getData(), lights.isDynamic());
	this->updateBuffer(camera.bindingPoint, camera.isDirty(), camera.id, sizeof(CameraUBO), &camera.getData(), camera.isDynamic());

	lights.cleanDirtyFlag();
	camera.cleanDirtyFlag();
}

void GlobalUniformsManager::updateBuffer(uint32_t bindingPoint, bool isDirty, uint32_t& id,
	size_t dataSize, const void* data, bool isDynamic)
{
	if (isDirty)
	{
		if (id == 0)
		{
			this->graphicsWrapper->createUniformBuffer(bindingPoint, id, dataSize, data, isDynamic);
		}
		else
		{
			this->graphicsWrapper->updateUniformBuffer(id, dataSize, data);
		}
	}
}

LightsUBO& GlobalUniformsManager::editLightsUBO()
{
	return this->buffersImpl->lights.editData();
}

CameraUBO& GlobalUniformsManager::editCameraUBO()
{
	return this->buffersImpl->camera.editData();
}

} // namespace
