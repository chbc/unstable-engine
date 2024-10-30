#include "SingletonsManager.h"
#include "MultimediaManager.h"
#include "RenderManager.h"
#include "AssetsManager.h"
#include "OpenGLESAPI.h"
#include "OpenGLAPI.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "MessagesManager.h"
#include "AtlasManager.h"
#include "ScenesManager.h"

namespace sre
{

UPTR<SingletonsManager> SingletonsManager::instance;

SingletonsManager::SingletonsManager()
{
    this->add<RenderManager>();
    this->add<MultimediaManager>();
    this->add<AssetsManager>();

#ifdef __ANDROID__
    this->add<AGraphicsWrapper, OpenGLESAPI>();
#else
    this->add<AGraphicsWrapper, OpenGLAPI>();
#endif

    this->add<ShaderManager>();
    this->add<LightManager>();
    this->add<TextureManager>();
    this->add<MessagesManager>();
    this->add<AtlasManager>();
    this->add<ScenesManager>();
}

SingletonsManager* SingletonsManager::getInstance()
{
    if (instance.get() == nullptr)
        instance = sre::make_unique<SingletonsManager>();

    return instance.get();
}

void SingletonsManager::init()
{
    for (std::pair<const std::string, UPTR<ASingleton>>& item : this->singletons)
        item.second->init();
}

void SingletonsManager::release()
{
    for (std::pair<const std::string, UPTR<ASingleton>>& item : this->singletons)
        item.second->preRelease();
	
    for (std::pair<const std::string, UPTR<ASingleton>> &item : this->singletons)
        item.second->release();

    this->singletons.clear();
}

} // namespace
