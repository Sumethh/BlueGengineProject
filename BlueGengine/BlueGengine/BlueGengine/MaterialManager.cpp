#include "MaterialManager.h"
#include "Material.h"
namespace BlueGengine
{

	MaterialManager::~MaterialManager()
	{

	}

	MaterialManager* MaterialManager::m_instance;

	Material* MaterialManager::CreateMaterial()
	{
		uint32 newMatId = m_materials.size();
		Material* returningMat = new Material(newMatId);
		m_materials.push_back(returningMat);
		return returningMat;
	}

}