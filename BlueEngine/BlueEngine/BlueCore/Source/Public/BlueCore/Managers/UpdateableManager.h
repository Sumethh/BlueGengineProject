#pragma once
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/Core/Defines.h"
#include <vector>

namespace Blue
{
	class UpdatableManager : NonCopyable
	{
	public:
		UpdatableManager();
		virtual ~UpdatableManager()
		{
			auto it = std::find(sUpdateableManagers.begin(), sUpdateableManagers.end(), this);

			if (it == sUpdateableManagers.end())
			{
				BlueAssert(false);
			}

			delete *it;
			sUpdateableManagers.erase(it);
		}
		virtual void Update() = 0;

		static void UpdateManagers()
		{
			for (auto manager : sUpdateableManagers)
			{
				manager->Update();
			}
		}
	private:
		static std::vector<UpdatableManager*> sUpdateableManagers;
	};
}