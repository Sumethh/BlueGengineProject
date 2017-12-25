#pragma once
#include "BlueCore/Managers/ASyncLoadingManager.h"
#include "BlueCore/Graphics/Mesh.h"
#include <functional>

namespace Blue
{
	struct AsyncLoadingMeshTracker : public AsyncLoadingManager::AsyncLoadingTracker
	{
	public:
		AsyncLoadingMeshTracker(std::future<bool>&& aFuture, uint64 aMeshID) : AsyncLoadingTracker(std::move(aFuture)), meshID(aMeshID)
		{
			callbacks.reserve(10);
		}

		void AddCallback(std::function<void(Mesh*)> aNewCallback)
		{
			callbacks.push_back(aNewCallback);
		}

		virtual void Completed() override
		{
			MeshManager::GI()->AsyncLoadComplete(this);
			Mesh* completedMesh = MeshManager::GI()->GetMesh(GetMeshID());			
			for (auto& func : callbacks)
			{
				func(completedMesh);
			}
		}

		virtual uint64 GetMeshID()
		{
			return meshID;
		}

	private:
		std::vector<std::function<void(Mesh*)>> callbacks;
		uint64 meshID;
	};
}