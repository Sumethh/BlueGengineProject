#include "Managers/UpdateableManager.h"
namespace BlueCore
{

	std::vector<UpdatableManager*> UpdatableManager::sUpdateableManagers;
	UpdatableManager::UpdatableManager()
	{
		sUpdateableManagers.push_back(this);
	}
}