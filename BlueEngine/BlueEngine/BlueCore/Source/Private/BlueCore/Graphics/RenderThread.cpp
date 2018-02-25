#include "BlueCore/Renderers/SceneRenderer.h"
#include "BlueCore/Graphics/RenderThread.h"
#include "BlueCore/Systems/TaskSystem.h"
#include "BlueCore/Containers/TWaitQueue.h"
#include "BlueCore/Core/ApplicationWindow.h"
#include "BlueCore/Managers/MaterialManager.h"
#include "BlueCore/GraphicsDevice/GraphicsDeviceFactory.h"
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
namespace Blue
{
	namespace RenderThread
	{
		const EThreadType threadType = EThreadType::RenderThread;
		std::atomic<bool> renderThreadRun;
		std::thread renderThread;

		SceneRenderer sceneRenderer;
		ApplicationWindow* window;
		std::condition_variable initVar;
		std::mutex renderThreadMutex;
		void RenderThreadMain()
		{
			window->MakeContextCurrent();
			window->SetVsync(0);
			IGraphicsDevice* gd = GraphicsDeviceFactory::GI()->CreateGraphicsDevice(EGraphicsDeviceType::OpenGL);
			gd->Init();
			gd->SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			
			MaterialManager::GI();
			SceneRenderer::GI()->Init();

			initVar.notify_all();
			window->MakeContextCurrent();
			while (renderThreadRun.load())
			{
				TaskSystem::ThreadRun(threadType);				
			}
		}

		void Init(ApplicationWindow* aWindow)
		{
			BlueAssert(aWindow);
			window = aWindow;
			renderThreadRun.store(true);
			renderThread = std::thread(&RenderThreadMain);

			std::unique_lock<std::mutex> lock(renderThreadMutex);
			initVar.wait(lock);
			aWindow = window;
		}

		void ShutDown()
		{
			renderThreadRun.store(false);
		}

		bool IsOnRenderThread()
		{
			return std::this_thread::get_id() == renderThread.get_id();
		}
	}
}