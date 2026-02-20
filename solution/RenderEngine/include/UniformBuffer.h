#pragma once

namespace sre
{

template <typename T>
class UniformBuffer
{
private:
	T data;
	uint32_t id{ 0 };
	bool dynamic{ false };
	uint32_t bindingPoint{ 0 };
	bool dirty{ false };

public:
	UniformBuffer(uint32_t arg_bindingPoint, bool arg_dynamic = false) 
		: bindingPoint(arg_bindingPoint), dynamic(arg_dynamic) { }

private:
	const T& getData() const
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
		return this->dirty;
	}

	void cleanDirtyFlag()
	{
		this->dirty = false;
	}

	bool isDynamic() const
	{
		return this->dynamic;
	}

friend class GlobalUniformsManager;
};

} // namespace
