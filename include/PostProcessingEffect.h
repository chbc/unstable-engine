#ifndef _POST_PROCESSING_EFFECT_H_
#define _POST_PROCESSING_EFFECT_H_

#include <unordered_map>
#include "memory_aliases.h"

namespace sre
{

namespace PPE
{
	enum Type
	{
		GRAYSCALE,
		INVERSE,
		ANTI_ALIASING,
		BLOOM,
		DEPTH_OF_FIELD
	};
} // namespace PPE

class PostProcessingEffect
{
private:
	PPE::Type type;
	std::unordered_map<std::string, UPTR<void*>> parameters;

private:
	PostProcessingEffect(PPE::Type effectType);

public:
	template <typename T>
	void setValue(const std::string& parameter, T value)
	{
		this->parameters[parameter] = value;
	}

	static PostProcessingEffect* create(PPE::Type effectType);

friend class PostProcessingComponent;
friend class ShaderContentFactory;
};

} // namespace

#endif
