#include "PostProcessingEffect.h"

namespace sre
{

PostProcessingEffect::PostProcessingEffect(PPE::Type effectType)
	: type(effectType)
{ }

PostProcessingEffect* PostProcessingEffect::create(PPE::Type effectType)
{
	PostProcessingEffect* result = new PostProcessingEffect(effectType);

	switch (effectType)
	{
		case PPE::GRAYSCALE:
		case PPE::INVERSE:
			break;
		case PPE::BLOOM: break;
		case PPE::DEPTH_OF_FIELD: break;
		default: break;
	}

	return result;
}

} // namespace
