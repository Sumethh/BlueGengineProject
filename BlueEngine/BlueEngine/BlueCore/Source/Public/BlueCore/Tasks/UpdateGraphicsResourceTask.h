#pragma once
#include "BlueCore/Systems/TaskSystem.h"

namespace Blue
{
	struct UpdateGraphicsResourceTask : public TaskSystem::Task
	{
		UpdateGraphicsResourceTask() : TaskSystem::Task("Update Graphics Resource", EThreadType::RenderThread, false)
		{
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
