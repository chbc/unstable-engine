#include "SingletonsManager.h"
#include "MultimediaManager.h"
#include "RenderManager.h"
#include "AssetsManager.h"
#include "OpenGLESAPI.h"
#include "OpenGLAPI.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "TextureCreator.h"
#include "MessagesManager.h"
#include "AtlasManager.h"
#include "ScenesManager.h"

namespace sre
{

UPTR<SingletonsManager> SingletonsManager::instance;

SingletonsManager::SingletonsManager()
{
    this->add<MultimediaManager>();
#ifdef __ANDROID__
    this->add<AGraphicsWrapper, OpenGLESAPI>();
#else
    this->add<AGraphicsWrapper, OpenGLAPI>();
#endif
    this->add<ShaderManager>();
    this->add<LightManager>();

    this->add<RenderManager>();
    this->add<AssetsManager>();


    this->add<TextureCreator>();
    this->add<MessagesManager>();
    this->add<AtlasManager>();
    this->add<ScenesManager>();
}

bool SingletonsManager::isInitialized()
{
    return (instance != nullptr);
}

SingletonsManager* SingletonsManager::loadInstance()
{
    if (instance.get() == nullptr)
        instance = sre::make_unique<SingletonsManager>();

    return instance.get();
}

void SingletonsManager::init()
{
    for (size_t i = 0; i < SINGLETONS_COUNT; ++i)
    {
        ASingleton* item = this->singletonsArray[i];
        item->init();
    }
}

void SingletonsManager::release()
{
    for (int i = SINGLETONS_COUNT - 1; i >= 0; --i)
    {
        ASingleton* item = this->singletonsArray[i];
        item->preRelease();
    }

    for (int i = SINGLETONS_COUNT - 1; i >= 0; --i)
    {
        ASingleton* item = this->singletonsArray[i];
        item->release();
    }

    this->singletons.clear();
}

} // namespace
