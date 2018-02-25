#pragma once
#include "BlueCore/Core/Types.h"

namespace Blue
{
	struct CapturedSceneInformation;
	class ApplicationWindow;
	class SceneRenderer;
	namespace RenderThread
	{
		void Init(ApplicationWindow* aWindow);
		void ShutDown();

		bool IsOnRenderThread();
	}
}
