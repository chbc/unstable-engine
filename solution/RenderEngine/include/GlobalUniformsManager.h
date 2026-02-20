#pragma once

#include "ASingleton.h"
#include "memory_aliases.h"

namespace sre
{

class AGraphicsWrapper;

class GlobalUniformsManager : public ASingleton
{
private:
	struct BuffersImpl;
	UPTR<BuffersImpl> buffersImpl;
	AGraphicsWrapper* graphicsWrapper{ nullptr };

public:
	GlobalUniformsManager();
	~GlobalUniformsManager();

protected:
	void init() override;
	void release() override;

private:
	void update();
	void updateBuffer(uint32_t bindingPoint, bool isDirty, uint32_t& id, 
		size_t dataSize, const void* data, bool isDynamic);
	struct LightsUBO& editLightsUBO();
	struct CameraUBO& editCameraUBO();

friend class SingletonsManager;
friend class LightManager;
friend class RenderManager;
friend class CameraComponent;
};

} // namespace
