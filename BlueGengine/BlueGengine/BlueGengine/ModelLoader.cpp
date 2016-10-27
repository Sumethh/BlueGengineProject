#include "ModelLoader.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Log.h"
#include "Defines.h"
#include "MeshManager.h"
//TODO: Implement the ability to load multiple meshes from a single file
namespace BlueGengine
{
	void LoadMesh(const aiScene& a_scene, Mesh* a_mesh, uint32 a_meshIndex)
	{
		std::cout << sizeof(Vertex) << std::endl;
		aiMesh* currentMesh = a_scene.mMeshes[a_meshIndex];


		if (!a_mesh)
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

		BlueGengine::Vertex* meshVertex = new BlueGengine::Vertex[vertCount];

		for (size_t i = 0; i < vertCount; i++)
		{
			BlueGengine::Vertex newVert = {};
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
		//a_mesh->Init(meshVertex, vertCount, indices, indiceCount);
		a_mesh->SetIndices(indices, indiceCount);
		a_mesh->SetVertices(meshVertex, vertCount);
		delete tangent;
		delete biTangent;
		delete verts;
		delete uvs;
		delete normals;
	}

	Mesh* ModelLoader::LoadModelFromFile(char* a_filePath)
	{
		Assimp::Importer importer;
		BlueAssert(a_filePath != nullptr);

		const aiScene* scene = importer.ReadFile(a_filePath, aiProcessPreset_TargetRealtime_Fast);

		BlueAssert(scene != nullptr);

		if (scene->HasMeshes())
		{
			Mesh* newMesh = MeshManager::GI()->CreateMesh();
			LoadMesh(*scene, newMesh, 0);
			return newMesh;
		}
		else
		{
			return nullptr;
		}
	}




}