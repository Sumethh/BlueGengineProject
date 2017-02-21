#include "Managers/UpdateableManager.h"

std::vector<UpdatableManager*> UpdatableManager::sUpdateableManagers;
UpdatableManager::UpdatableManager()
{
	sUpdateableManagers.push_back(this);
}