#include "ModelNode.h"

#include <QDebug>

namespace nodes
{

ModelNode::ModelNode(SceneManager *sceneManager, const char *fileName) : RenderableNode(sceneManager)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_GenSmoothNormals | aiProcess_Triangulate | /* XXX aiProcess_CalcTangentSpace |*/ aiProcess_FlipUVs);

    if ((scene == NULL) || (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) || (scene->mRootNode == NULL))
    {
        qDebug() << "Could not import: " << fileName;
        return;
    }

    this->recursiveProcess(scene->mRootNode, scene);
}

ModelNode::~ModelNode()
{
    for (int i = 0; i < this->meshes.size(); i++)
        delete this->meshes[i];
}

void ModelNode::recursiveProcess(aiNode *node, const aiScene *scene)
{
    // process
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->processMesh(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
        this->recursiveProcess(node->mChildren[i], scene);
}

void ModelNode::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<VertexData> vertexData;
    std::vector<unsigned int> indices;

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    aiColor4D color;
    aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
    Vector defaultColor(color.r, color.g, color.b);

    for (unsigned int i = 0; i  < mesh->mNumVertices; i++)
    {
        VertexData tmp;
        Vector tmpVec;

        // position
        tmpVec.x = mesh->mVertices[i].x;
        tmpVec.y = mesh->mVertices[i].y;
        tmpVec.z = mesh->mVertices[i].z;
        tmp.position = tmpVec;

        // normal
        tmpVec.x = mesh->mNormals[i].x;
        tmpVec.y = mesh->mNormals[i].y;
        tmpVec.z = mesh->mNormals[i].z;
        tmp.normal = tmpVec;

        // color
        if (mesh->mColors[0] != NULL)
        {
            tmpVec.x = mesh->mColors[0][i].r;
            tmpVec.y = mesh->mColors[0][i].g;
            tmpVec.z = mesh->mColors[0][i].b;
        }
        else
            tmpVec = defaultColor;

        tmp.color = tmpVec;

        // tex coord
        if (mesh->mTextureCoords[0] != NULL)
        {
            tmpVec.x = mesh->mTextureCoords[0][i].x;
            tmpVec.y = mesh->mTextureCoords[0][i].y;
        }
        else
            tmpVec.x = tmpVec.y = tmpVec.z = 0.0f;

        tmp.u = tmpVec.x;
        tmp.v = tmpVec.y;

        vertexData.push_back(tmp);
    }

    // indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) // 0..2
            indices.push_back(face.mIndices[j]);
    }

    // materials and textures
    /* XXX
    for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
    {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, i, &str);
        Texture *texture =
        tmp.id = loadTexture(str.C_Str());
        tmp.type = 0;
        textureData.push_back(tmp);
    }
    */

    this->meshes.push_back(new Mesh(&vertexData, &indices));
}

} // namespace nodes
