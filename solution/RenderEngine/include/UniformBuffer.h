#pragma once

namespace sre
{

template <typename T>
class UniformBuffer
{
private:
	T data;
	uint32_t id{ 0 };
	uint32_t bindingPoint{ 0 };
	bool dirty{ false };

public:
	UniformBuffer(uint32_t arg_bindingPoint) : bindingPoint(arg_bindingPoint) { }

private:
	T& getData()
	{
		return this->data;
	}

	T& editData()
	{
		this->dirty = true;
		return this->data;
	}

	bool isDirty() const
	{
		return true;
	}

	void cleanDirtyFlag()
	{
		this->dirty = false;
	}

friend class GlobalUniformsManager;
};

} // namespace
