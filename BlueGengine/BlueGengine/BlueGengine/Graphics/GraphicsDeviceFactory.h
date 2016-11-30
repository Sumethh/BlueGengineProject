#pragma once
#include "../NonCopyable.h"
#include "IGraphicsDevice.h"
namespace BlueGengine
{
	class IGraphicsDevice;
	class GraphicsDeviceFactory : NonCopyable
	{
		public:
		GraphicsDeviceFactory();

		static inline GraphicsDeviceFactory* GI()
		{
			if (!sFactoryInstance)
			{
				sFactoryInstance = new GraphicsDeviceFactory();
			}

			return sFactoryInstance;
		}

		IGraphicsDevice* CreateGraphicsDevice(EGraphicsDeviceType aType);
		private:
		static GraphicsDeviceFactory* sFactoryInstance;
	};
}
