#pragma  once
#include "BlueCore/Systems/TaskSystem.h"

namespace Blue
{
	struct CreateGraphicsResourceTask : public TaskSystem::Task
	{
		UpdateGraphicsResourceTask() : TaskSystem::Task("Create Graphics Resource", false)
		{
			threadType = EThreadType::RenderThread;
		}

		virtual void Run() override
		{
			BlueAssert(graphicsResourceToCreate);	
		}

		virtual bool IsCompleted() override
		{
			return true;
		}

		GraphicsResource* graphicsResourceToCreate;
	};
}
