#include "SampleApplication.h"
#include "contexts/MainMenuContext.h"
#include "contexts/GameContext.h"
#include <MeshComponent.h>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	GameContext::load(this->scenesManager.get());
}

float time = 0;
int indice = 0;

void SampleApplication::onUpdate(float elapsedTime)
{
	if (Input::isKeyJustPressed(KEY_a))
	{
		std::function<void()> loadFunction = [&](void) {MainMenuContext::load(this->scenesManager.get()); };
		TEMP_loadScene(loadFunction);
	}
	if (Input::isKeyJustPressed(KEY_s))
	{
		std::function<void()> loadFunction = [&](void) {GameContext::load(this->scenesManager.get()); };
		TEMP_loadScene(loadFunction);
	}

	time += elapsedTime;
	if (time > 0.1f)
	{
		time = 0;
		indice = indice++ % 6;
		glm::vec2 uvOffset{ indice * 0.1666f, 0.0f };

		Entity* entity = this->scenesManager->getEntity("coin");
		Material* material = entity->getComponent<MeshComponent>()->getMaterial();
		material->setUVOffset(uvOffset);
	}
}
