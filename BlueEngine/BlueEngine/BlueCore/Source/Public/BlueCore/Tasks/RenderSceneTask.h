#pragma once
#include "BlueCore/Systems/TaskSystem.h"
#include "BlueCore/Core/Scene.h"
#include "BlueCore/Renderers/SceneRenderer.h"
#include "BlueCore/Core/ApplicationWindow.h"
#include "BlueCore/Graphics/RenderThread.h"
#include "BlueCore/Core/Log.h"
#include <future>
namespace Blue
{
	struct RenderSceneTask : public TaskSystem::Task
	{
		RenderSceneTask() : TaskSystem::Task("Render Scene", EThreadType::RenderThread, false)
		{
		}

		virtual void Run() override
		{
			BlueAssert(RenderThread::IsOnRenderThread());
			ApplicationWindow* window = ApplicationWindow::GetCurrentWindow();
			window->ClearScreen();
			SceneRenderer* renderer = SceneRenderer::GI();
			renderer->CaptureScene(sceneToRender);
			promise.set_value(true);
			renderer->ConductScenePass();
		}
		virtual bool IsCompleted() override
		{
			return true;
		}

		Scene* sceneToRender;
		std::promise<bool> promise;
	};
}