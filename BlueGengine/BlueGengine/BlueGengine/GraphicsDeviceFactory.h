#pragma once
#include "NonCopyable.h"
namespace BlueGengine
{
	class GraphicsDevice;
	class GraphicsDeviceFactory : NonCopyable
	{
		public:
		GraphicsDeviceFactory();

		inline GraphicsDeviceFactory* GetInstance()
		{
			if (!sFactoryInstance)
			{
				sFactoryInstance = new GraphicsDeviceFactory();
			}

			return sFactoryInstance;
		}

		GraphicsDevice* CreateGraphicsDevice(EGraphicsDeviceType aType);
		private:
		static GraphicsDeviceFactory* sFactoryInstance;
	};
}
