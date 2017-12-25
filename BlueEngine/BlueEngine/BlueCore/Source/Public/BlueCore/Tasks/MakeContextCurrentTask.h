#pragma once
#include "BlueCore/Systems/TaskSystem.h"
#include "BlueCore/Core/ApplicationWindow.h"
namespace Blue
{
	struct MakeContextCurrentTask : TaskSystem::Task
	{
	public:
		MakeContextCurrentTask(ApplicationWindow* aContextToSwitchTo) : TaskSystem::Task("MakeContextCurrentTask", false), contextToSwitchTo(aContextToSwitchTo)
		{

		}
		virtual ~MakeContextCurrentTask()
		{

		}

		virtual void Run() override
		{
			BlueAssert(contextToSwitchTo);
			contextToSwitchTo->MakeContextCurrent();
		}

		virtual bool IsCompleted() override
		{
			return true;
		}

	private:
		ApplicationWindow * contextToSwitchTo;
	};
}
