#pragma once

#include "ASingleton.h"
#include "memory_aliases.h"

namespace sre
{

class AGraphicsWrapper;
struct BuffersImpl;

class GlobalUniformsManager : public ASingleton
{
private:
	AGraphicsWrapper* graphicsWrapper{ nullptr };
	UPTR<BuffersImpl> buffersImpl;

public:
	GlobalUniformsManager();
	~GlobalUniformsManager();

protected:
	void init() override;
	void release() override;

private:
	void update();
	void updateBuffer(uint32_t bindingPoint, bool isDirty, uint32_t& id, size_t dataSize, void* data);
	struct LightsUBO& editLightsUBO();

friend class SingletonsManager;
friend class LightManager;
friend class RenderManager;
};

} // namespace
