#pragma once
#include "BlueCore/Systems/TaskSystem.h"

namespace Blue
{
	struct UpdateGrapihcsResourceTask : public TaskSystem::Task
	{
		UpdateGrapihcsResourceTask() : TaskSystem::Task("Update Graphics Resource", false)
		{
			threadType = EThreadType::RenderThread;
		}

		virtual void Run() override
		{
			BlueAssert(graphicsResourceToUpdate);
			if (!graphicsResourceToUpdate->IsValid())
			{
				graphicsResourceToUpdate->Create();
			}
			graphicsResourceToUpdate->UpdateResource();
		}

		virtual bool IsCompleted() override
		{
			return true;
		}
		
		GraphicsResource* graphicsResourceToUpdate;

	};
}
