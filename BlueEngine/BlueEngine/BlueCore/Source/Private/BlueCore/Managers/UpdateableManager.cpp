#include "BlueCore/Managers/UpdateableManager.h"

namespace Blue
{
	std::vector<UpdatableManager*> UpdatableManager::sUpdateableManagers;
	UpdatableManager::UpdatableManager()
	{
		sUpdateableManagers.emplace_back(this);
	}
}