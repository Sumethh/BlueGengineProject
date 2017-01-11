#pragma once
#include "../Core/NonCopyable.h"
#include "IGraphicsDevice.h"
namespace BlueCore
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
