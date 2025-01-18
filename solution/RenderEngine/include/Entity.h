// XXX
// USAR MACRO PRA SUBSTITUIR O TPP
// USAR MACRO NO CORPO DOS COMPONENTES PRA IMPLEMENTAR O getComponent()

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "AEntityComponent.h"
#include "TransformComponent.h"
#include "memory_aliases.h"
#include "EntityTypes.h"

#include <unordered_map>
#include <vector>
#include <string>

namespace sre
{

#define DECLARE_ENTITY() \
    public: \
        static bool _xxx_;

#define IMPLEMENT_ENTITY(EntityClass) \
    bool EntityClass::_xxx_ = Entity::AddType<EntityClass>(#EntityClass);

class Entity
{
DECLARE_ENTITY()

private:
	std::unordered_map<uint16_t, UPTR<AEntityComponent>> componentsMap;
    std::vector<SPTR<AEditorProperty>> editorProperties;
    Entity* parent{ nullptr };
    std::unordered_map<std::string, UPTR<Entity>> children;
    std::vector<Entity*> childrenList;

	TransformComponent* transform;

    bool alive{ true };
    bool enabled{ true };
    uint32_t childIndex{};
    std::string name;
    std::string fileName;

public:
    SRE_API Entity(std::string arg_name);
    SRE_API virtual ~Entity();

    template <typename T> T* addComponent();
    template <typename T> void removeComponent();
    template <typename T> T* getComponent();
    template <typename T> bool hasComponent();

    AEntityComponent* addComponent(const char* className);

    Entity* createChild(const std::string& childName = "", const char* className = nullptr);
	SRE_API void addChild(Entity *child);
	SRE_API inline size_t getChildrenCount() { return this->children.size(); }
	SRE_API Entity *getChild(size_t index);
	SRE_API inline Entity *getParent() { return this->parent; }

	SRE_API TransformComponent *getTransform();

	SRE_API void destroy();
	SRE_API inline bool isAlive() const { return this->alive; }
    SRE_API const char* getName() const { return this->name.c_str(); }

    SRE_API void setEnabled(bool value);
    SRE_API bool isEnabled() const;

    template <typename Type>
    static bool AddType(const char* className)
    {
        EntityTypes* types = EntityTypes::getInstance();
        types->addType<Type>(className);
        return true;
    }

protected:
	SRE_API virtual void onInit();
	SRE_API virtual void onUpdate(float elapsedTime);
    SRE_API virtual void onValueChanged() {}
    SRE_API void addEditorProperty(AEditorProperty* editorProperty);

private:
    static Entity* Create(std::string arg_name, const char* className);
    static std::string generateEntityId(uint32_t& index, const std::string& duplicateName = "");
    template <typename T> uint16_t getComponentId();

    friend class AScene;
    friend class EntityLoader;
    friend class EntityParser;
    friend class AssetsManager;

    friend class TestServicesProvider;
    friend class EditorEntityProperties;
    friend class EditorSceneViewport;
};

} // namespace

#include "Entity.tpp"

#endif
