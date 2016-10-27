#include "MeshManager.h"
#include "Mesh.h"
#include <vector>
#include "ModelLoader.h"
namespace BlueGengine
{

	MeshManager::~MeshManager()
	{
	}

	MeshManager* MeshManager::m_instance = nullptr;
	Mesh* MeshManager::CreateMesh()
	{
		uint32 nextId = (uint32)m_meshList.size();
		Mesh* newMesh = new Mesh(nextId);
		m_meshList.push_back(newMesh);
		return newMesh;
	}
}