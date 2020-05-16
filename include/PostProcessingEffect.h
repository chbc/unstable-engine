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
		BLUR,
		BLOOM,
		HDR,
		DOF,
		OUTLINE
	};
} // namespace PPE

class PostProcessingEffect
{
private:
	PPE::Type type;
	std::unordered_map<std::string, float> parameters;

private:
	PostProcessingEffect(PPE::Type effectType);

public:
	void setValue(const std::string& parameter, float value)
	{
		this->parameters[parameter] = value;
	}

	float getValue(const std::string& parameter)
	{
		return this->parameters[parameter];
	}

	static PostProcessingEffect* create(PPE::Type effectType);

	PPE::Type getType() { return this->type; }

friend class PostProcessingComponent;
friend class ShaderContentFactory;
};

} // namespace

#endif
