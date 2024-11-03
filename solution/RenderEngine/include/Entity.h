// XXX
// USAR MACRO PRA SUBSTITUIR O TPP
// USAR MACRO NO CORPO DOS COMPONENTES PRA IMPLEMENTAR O getComponent()

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "AEntityComponent.h"
#include "TransformComponent.h"
#include "memory_aliases.h"

#include <unordered_map>
#include <vector>
#include <string>

namespace sre
{

/*!
    Class that represents a node of the scene.
*/
class Entity
{
private:
	std::unordered_map<uint16_t, UPTR<AEntityComponent>> componentsMap;
    Entity *parent;
    std::unordered_map<std::string, UPTR<Entity>> children;
    std::vector<Entity*> childrenList;

	TransformComponent* transform;

    bool alive;
    bool enabled;
    uint32_t childIndex{};
    std::string name;

protected:
    SRE_API Entity();

public:
    SRE_API ~Entity();

    template <typename T> T* addComponent();
    template <typename T> void removeComponent();
    template <typename T> T* getComponent();
    template <typename T> bool hasComponent();

    AEntityComponent* addComponent(const char* className);

	SRE_API void addChild(Entity *child, const std::string& childName = "");
	SRE_API inline uint32_t getChildrenCount() { return this->children.size(); }
	SRE_API Entity *getChild(uint32_t index);
	SRE_API inline Entity *getParent() { return this->parent; }

	SRE_API TransformComponent *getTransform();

	SRE_API void destroy();
	SRE_API inline bool isAlive() const { return this->alive; }
    SRE_API const char* getName() const { return this->name.c_str(); }

    SRE_API void setEnabled(bool value);
    SRE_API bool isEnabled() const;

protected:
	virtual void onInit();
	virtual void onUpdate(float deltaTime);

private:
    static std::string generateEntityId(uint32_t& index, const std::string& duplicateName = "");
    template <typename T> uint16_t getComponentId();

    friend class AScene;
    friend class ModelLoader;
    friend class EntityParser;

    friend class TestServicesProvider;
    friend class EditorEntityProperties;
    friend class EditorSceneViewport;
};

} // namespace

#include "Entity.tpp"

#endif
