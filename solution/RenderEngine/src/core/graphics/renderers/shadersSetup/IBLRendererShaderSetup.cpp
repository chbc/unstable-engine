#include "IBLRendererShaderSetup.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "ETextureMap.h"

namespace sre
{

IBLRendererShaderSetup::IBLRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : BaseRendererShaderSetup(shaderManager, graphicsWrapper)
{
    this->lightManager = SingletonsManager::getInstance()->get<LightManager>();
}

void IBLRendererShaderSetup::onSceneLoaded(uint32_t program)
{
	this->shaderManager->setupUniformLocation(program, ShaderVariables::IBL_IRRADIANCE);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::IBL_PREFILTER);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::IBL_BRDF_LUT);
}

void IBLRendererShaderSetup::setupShaderValues(uint32_t program)
{
	const IBLData& iblData = this->lightManager->getIBLData();
	this->graphicsWrapper->activateCubeMapTexture(iblData.irradianceMap, ETextureMap::IBL_IRRADIANCE);
	this->graphicsWrapper->activateCubeMapTexture(iblData.prefilterMap, ETextureMap::IBL_PREFILTER);
	this->graphicsWrapper->activateTexture(iblData.brdfLUTMap, ETextureMap::IBL_BRDF_LUT);

	this->shaderManager->setInt(program, ShaderVariables::IBL_IRRADIANCE, ETextureMap::IBL_IRRADIANCE);
	this->shaderManager->setInt(program, ShaderVariables::IBL_PREFILTER, ETextureMap::IBL_PREFILTER);
	this->shaderManager->setInt(program, ShaderVariables::IBL_BRDF_LUT, ETextureMap::IBL_BRDF_LUT);
}

} // namespace
