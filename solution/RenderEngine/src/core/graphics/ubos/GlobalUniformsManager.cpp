#include "GlobalUniformsManager.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "UniformBuffer.h"
#include "LightsUBO.h"

namespace sre
{

struct BuffersImpl
{
	UniformBuffer<LightsUBO> lights{ 0 };
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
	this->graphicsWrapper->deleteUniformBuffer(this->buffersImpl->lights.id);
}

void GlobalUniformsManager::update()
{
	UniformBuffer<LightsUBO>& lights = this->buffersImpl->lights;
	this->updateBuffer(lights.bindingPoint, lights.isDirty(), lights.id, sizeof(LightsUBO), &lights.getData());

	lights.cleanDirtyFlag();
}

void GlobalUniformsManager::updateBuffer(uint32_t bindingPoint, bool isDirty, uint32_t& id, size_t dataSize, void* data)
{
	if (isDirty)
	{
		if (id == 0)
		{
			this->graphicsWrapper->createUniformBuffer(bindingPoint, id, dataSize, data);
		}
		else
		{
			this->graphicsWrapper->updateUniformBuffer(bindingPoint, id, dataSize, data);
		}
	}
}

LightsUBO& GlobalUniformsManager::editLightsUBO()
{
	return this->buffersImpl->lights.editData();
}

} // namespace
