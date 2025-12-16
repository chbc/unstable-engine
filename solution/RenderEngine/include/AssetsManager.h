#pragma once

#include "core_defines.h"
#include "ASingleton.h"
#include "AssetsCollection.h"
#include "ETextureMap.h"
#include "EGuizmoMesh.h"

namespace sre
{

class Entity;
struct Model;
struct Model2D;
struct MeshData;
struct MeshData2D;
class ABaseMaterial;
class Texture;
struct ColorMeshData;

class AScene;

using GuizmosCollection = std::unordered_map<EGuizmoMesh, SPTR<ColorMeshData>>;

class SRE_API AssetsManager : public ASingleton
{
private:
	AssetsCollection entitiesCollection;
	AssetsCollection modelsCollection;
	AssetsCollection models2DCollection;
	AssetsCollection materialsCollection;
	AssetsCollection texturesCollection;
	AssetsCollection iconsCollection;
	GuizmosCollection guizmosCollection;

public:
	Entity* loadEntity(AScene* scene, const char* filePath, std::string name);
	Model* loadModel(const std::string& filePath);
	MeshData* loadMesh(const char* filePath, const char* meshName);
	MeshData2D* loadMesh2D();
	ABaseMaterial* loadMaterial(const std::string& filePath, size_t referencesCount = 1);
	Texture* loadTexture(const char* filePath, ETextureMap::Type mapType);
	Texture* loadIcon(const char* filePath);
	ColorMeshData* loadGuizmo(EGuizmoMesh type);

	void releaseEntity(Entity* entity);
	void releaseModel(const char* filePath);
	void releaseModel2D(Model2D* model);
	void releaseMaterial(ABaseMaterial* material);
	void releaseTexture(Texture* texture);
	void releaseIcon(Texture* texture);

protected:
	void preRelease() override;
};

} // namespace
