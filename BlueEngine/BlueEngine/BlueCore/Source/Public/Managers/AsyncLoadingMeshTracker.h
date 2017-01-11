#pragma once
#include "Managers/ASyncLoadingManager.h"
#include "Graphics/Mesh.h"
#include <functional>

namespace BlueCore
{
	struct AsyncLoadingMeshTracker : public AsyncLoadingManager::IAsyncLoadingTracker
	{
		public:
		AsyncLoadingMeshTracker(std::future<bool>&& aFuture, Mesh* aMesh) : IAsyncLoadingTracker(std::move(aFuture)),
								loadingMesh(aMesh)
		{
			callbacks.reserve(10);
		}
		void AddCallback(std::function<void(Mesh*)> aNewCallback)
		{
			callbacks.push_back(aNewCallback);
		}

		void SetMeshResources()
		{
			loadingMesh->UpdateMeshResources();
		}

		virtual void Completed() override
		{
			SetMeshResources();

			for (auto& func : callbacks)
			{
				func(loadingMesh);
			}

			MeshManager::GI()->AsyncLoadComplete(this);

		}

		const Mesh* GetMesh() { return loadingMesh; }
		private:
		std::vector<std::function<void(Mesh*)>> callbacks;
		Mesh* loadingMesh;
	};
}