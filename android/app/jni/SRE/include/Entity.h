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
	std::unordered_map<int, UPTR<AEntityComponent>> componentsMap;
    Entity *parent;
    std::vector<Entity*> children;

	TransformComponent* transform;

    bool alive;
    bool enabled;
    uint32_t childIndex{};
    std::string name;

protected:
    SRE_API Entity();

public:
    SRE_API virtual ~Entity();

    template <typename T, typename... TArgs> T* addComponent(TArgs&&... mArgs);
    template <typename T> void removeComponent();
    template <typename T> T* getComponent();
    template <typename T> bool hasComponent();

	SRE_API void addChild(Entity *child, const std::string& name = "");
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
	void SRE_API onStart();
	void SRE_API update(uint32_t deltaTime);

private:
    static std::string generateEntityId(uint32_t& index, const std::string& duplicateName = "");
    template <typename T> int getComponentId();

    friend class AEntityManager;
    friend class ModelLoader;

    friend class TestServicesProvider;
};

} // namespace

#include "Entity.tpp"

#endif
