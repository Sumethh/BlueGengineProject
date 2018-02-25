#pragma once
#include "BlueCore/Systems/TaskSystem.h"
#include "BlueCore/Core/ApplicationWindow.h"
#include "BlueCore/Graphics/RenderThread.h"
#include <future>
namespace Blue
{
	struct WindowSwapTask : public TaskSystem::Task
	{
		WindowSwapTask() : TaskSystem::Task("Swap Window", EThreadType::RenderThread, false)
		{
		}

		virtual void Run() override
		{
			BlueAssert(RenderThread::IsOnRenderThread());
			window->Swap();
		}
		virtual bool IsCompleted() override
		{
			return true;
		}

		ApplicationWindow* window;
	};
}
