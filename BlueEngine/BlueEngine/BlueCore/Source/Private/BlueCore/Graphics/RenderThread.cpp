#include "BlueCore/Renderers/SceneRenderer.h"
#include "BlueCore/Graphics/RenderThread.h"
#include "BlueCore/Systems/TaskSystem.h"
#include "BlueCore/Containers/TWaitQueue.h"

#include <thread>
#include <atomic>
namespace Blue
{
	struct CapturedSceneInformation;
	namespace RenderThread
	{
		const EThreadType threadType = EThreadType::RenderThread;
		std::atomic<bool> renderThreadRun;
		std::thread renderThread;

		SceneRenderer sceneRenderer;
		TWaitQueue<CapturedSceneInformation*> sceneRenderList;
		void RenderThreadMain()
		{
			while (renderThreadRun.load())
			{
				TaskSystem::ThreadRun(threadType);
				std::this_thread::yield();
			}
		}
		
		void Init(ApplicationWindow* aWindow)
		{
			BlueAssert(aWindow);
			renderThreadRun.store(true);		
			renderThread = std::thread(&RenderThreadMain);
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