// XXX
// USAR MACRO PRA SUBSTITUIR O TPP
// USAR MACRO NO CORPO DOS COMPONENTES PRA IMPLEMENTAR O getComponent()

#pragma once

#include "AEntityComponent.h"
#include "TransformComponent.h"
#include "memory_aliases.h"
#include "EntityTypes.h"
#include "Bounds.h"

#include <unordered_map>
#include <vector>
#include <string>

namespace sre
{

#define DECLARE_ENTITY() \
    public: \
        static const char* CLASS_NAME; \
        const char* getClassName() const override { return CLASS_NAME; }

#define IMPLEMENT_ENTITY(EntityClass) \
    const char* EntityClass::CLASS_NAME = Entity::AddType<EntityClass>(#EntityClass);

class Entity
{

private:
    static const char* BASE_CLASS_NAME;

	std::unordered_map<uint16_t, UPTR<AEntityComponent>> componentsMap;
    std::vector<SPTR<AEditorProperty>> editorProperties;
    Entity* parent{ nullptr };
    std::unordered_map<std::string, UPTR<Entity>> children;
    std::vector<Entity*> childrenList;
    bool alive{ true };
    bool enabled{ true };
    std::string name;
    std::string filePath;
    bool propertiesSaved{ true };
    bool componentsSaved{ true };
    bool childrenSaved{ true };
    bool propertiesStored{ true };
    bool componentsStored{ true };
    bool childrenStored{ true };
	bool dontShowInEditorSceneTree{ false };

protected:
	TransformComponent* transform;

public:
    SRE_API Entity(std::string arg_name);
    SRE_API virtual ~Entity();

    template <typename T> T* addComponent();
    template <typename T> void removeComponent();
    template <typename T> T* getComponent();
    template <typename T> void getComponents(std::vector<T*>& result);
    template <typename T> bool hasComponent();

    AEntityComponent* addComponent(const char* className);

	SRE_API Entity* addChild(Entity *child);
    SRE_API Entity* addChild(UPTR<Entity>& child);
	SRE_API void removeChild(Entity* child);
	SRE_API inline size_t getChildrenCount() { return this->children.size(); }
	SRE_API Entity *getChild(size_t index);
	SRE_API Entity* getChild(const std::string& name);
    SRE_API UPTR<Entity> moveChild(const std::string& name);
	SRE_API inline Entity *getParent() { return this->parent; }

	SRE_API TransformComponent *getTransform();

	SRE_API void destroy();
	SRE_API inline bool isAlive() const { return this->alive; }
    SRE_API const char* getName() const { return this->name.c_str(); }

    SRE_API void setEnabled(bool value, bool changeChildren = false);
    SRE_API bool isEnabled() const;

    template <typename Type>
    static const char* AddType(const char* className)
    {
        EntityTypes* types = EntityTypes::getInstance();
        types->addType<Type>(className);
        return className;
    }

    virtual const char* getClassName() const;

	SRE_API void getBounds(Bounds& bounds) const;
	SRE_API void setDontShowInEditorSceneTree(bool value);
    SRE_API bool raycast(const Ray& ray, float& distance);
    SRE_API Entity* raycastChildren(const Ray& ray, float maxDistance);

protected:
	SRE_API virtual void onInit();
	SRE_API virtual void onUpdate(float elapsedTime);
    SRE_API void addEditorProperty(AEditorProperty* editorProperty);

private:
    void onPropertySerialized() {}
    void onPropertyDeserialized();
    void onPropertyChanged();
    void onComponentDeserialized();
    void onComponentChanged();
    void onChildChanged();
    void getBounds(Bounds& bounds, bool& baseEntity) const;
    void setPropertiesSaved();
    void setComponentsSaved();
    void setChildrenSaved();
    void setStored(bool value);
    bool isPropertiesSaved() const;
    bool isComponentsSaved() const;
    bool isChildrenSaved() const;
    bool isPropertiesStored() const;
    bool isComponentsStored() const;
    bool isChildrenStored() const;
    bool isAsset() const;
    bool isStored() const;
    bool isSaved() const;
    Entity* clone();
	void removeDestroyedChildren();
    AEditorProperty* findProperty(const std::string& title);
    static Entity* Create(std::string arg_name, const std::string& className);
    template <typename T> uint16_t getComponentId();

    friend class AScene;
    friend class SceneLoader;
    friend class EntityLoader;
    friend class EntityParser;
    friend class AssetsManager;
    friend class AEntityComponent;

    friend class TestServicesProvider;
    friend class EditorEntityProperties;
    friend class SceneViewportCamera;
    friend class EditorsController;
    friend class EditorSceneTree;
    friend class ScenesManager;
};

} // namespace

#include "Entity.tpp"
