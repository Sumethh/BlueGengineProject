#include "BlueCore/Managers/UpdateableManager.h"

namespace Blue
{
	std::vector<UpdatableManager*> UpdatableManager::sUpdateableManagers;
	UpdatableManager::UpdatableManager()
	{
		sUpdateableManagers.push_back(this);
	}
}