#pragma once
#include "BlueCore/Core/Types.h"

namespace Blue
{
	class ApplicationWindow;
	namespace RenderThread
	{
		void Init(ApplicationWindow* aWindow);
		void ShutDown();

		bool IsOnRenderThread();
	}
}
