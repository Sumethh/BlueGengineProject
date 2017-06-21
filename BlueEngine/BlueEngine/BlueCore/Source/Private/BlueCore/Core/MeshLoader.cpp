#include "BlueCore/Graphics/MeshLoader.h"
#include "BlueCore/Graphics/Mesh.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Managers/MeshManager.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Blue
{
	//TODO: Implement the ability to load multiple meshes from a single file

	void LoadMesh(const aiScene& aScene, Mesh* aMesh, uint32 aMeshIndex)
	{
		aiMesh* currentMesh = aScene.mMeshes[aMeshIndex];


		if (!aMesh)
		{
			//Log.LogError("Got passed a null mesh");
			return;
		}

		uint32 vertCount = currentMesh->mNumVertices;

		glm::vec3* verts = new glm::vec3[vertCount];

		for (size_t i = 0; i < currentMesh->mNumVertices; i++)
		{
			aiVector3D vert = currentMesh->mVertices[i];
			verts[i] = glm::vec3(vert.x, vert.y, vert.z);
		}

		glm::vec3* normals = nullptr;


		if (currentMesh->HasNormals())
		{
			normals = new glm::vec3[vertCount];

			for (size_t i = 0; i < currentMesh->mNumVertices; i++)
			{
				aiVector3D normal = currentMesh->mNormals[i];
				normals[i] = glm::vec3(normal.x, normal.y, normal.z);
			}
		}

		glm::vec2* uvs = nullptr;

		if (currentMesh->HasTextureCoords(0))
		{
			uvs = new glm::vec2[vertCount];

			for (size_t i = 0; i < currentMesh->mNumVertices; i++)
			{
				aiVector3D uv = currentMesh->mTextureCoords[0][i];
				uvs[i] = glm::vec2(uv.x, uv.y);
			}
		}

		uint32* indices = nullptr;
		uint32 indiceCount = 0;

		if (currentMesh->HasFaces())
		{
			indiceCount = currentMesh->mNumFaces * 3;
			indices = new uint32[indiceCount];
			int indc = 0;

			for (size_t i = 0; i < currentMesh->mNumFaces; i++)
			{
				for (size_t x = 0; x < currentMesh->mFaces[i].mNumIndices; x++)
				{
					indices[i * 3 + x] = (currentMesh->mFaces[i].mIndices[x]);
					indc++;
				}
			}
		}

		glm::vec3* tangent = nullptr;
		glm::vec3* biTangent = nullptr;

		if (currentMesh->HasTangentsAndBitangents())
		{

			tangent = new glm::vec3[vertCount];
			biTangent = new glm::vec3[vertCount];

			for (size_t i = 0; i < currentMesh->mNumVertices; i++)
			{
				glm::vec3 t(currentMesh->mTangents[i].x, currentMesh->mTangents[i].y, currentMesh->mTangents[i].z);
				glm::vec3 bt(currentMesh->mBitangents[i].x, currentMesh->mBitangents[i].y, currentMesh->mBitangents[i].z);
				tangent[i] = t;
				biTangent[i] = bt;
			}
		}

		Vertex* meshVertex = new Vertex[vertCount];

		for (size_t i = 0; i < vertCount; i++)
		{
			Vertex newVert = {};
			newVert.position = verts[i];
			newVert.normal = normals[i];

			newVert.uv = uvs[i];


			if (tangent)
			{
				newVert.tangent = tangent[i];
			}

			if (biTangent)
			{
				newVert.biTangent = biTangent[i];
			}

			meshVertex[i] = newVert;

		}

		//TODO: clean up the model loader so that there are no unescesary allocs
		//aMesh->Init(meshVertex, vertCount, indices, indiceCount);
		aMesh->SetIndices(indices, indiceCount);
		aMesh->SetVertices(meshVertex, vertCount);
		delete tangent;
		delete biTangent;
		delete verts;
		delete uvs;
		delete normals;
	}

	Mesh* MeshLoader::LoadMeshFromFile(char* aFilePath, std::string aMeshName)
	{
		Assimp::Importer importer;
		BlueAssert(aFilePath != nullptr);

		const aiScene* scene = importer.ReadFile(aFilePath, aiProcessPreset_TargetRealtime_Fast);

		if (scene == nullptr)
		{
			return nullptr;
		}

		if (scene->HasMeshes())
		{
			Mesh* newMesh = MeshManager::GI()->CreateMesh(aMeshName);
			LoadMesh(*scene, newMesh, 0);
			return newMesh;
		}
		else
		{
			return nullptr;
		}
	}

	Mesh* MeshLoader::LoadMeshFromFile(std::string aFilePath, std::string aMeshName, Mesh* aMesh)
	{
		Assimp::Importer importer;
		BlueAssert(aFilePath.size());

		const aiScene* scene = importer.ReadFile(aFilePath, aiProcessPreset_TargetRealtime_Fast);

		BlueAssert(scene != nullptr);

		if (scene->HasMeshes())
		{
			LoadMesh(*scene, aMesh, 0);
			return aMesh;
		}
		else
		{
			return nullptr;
		}
	}
}