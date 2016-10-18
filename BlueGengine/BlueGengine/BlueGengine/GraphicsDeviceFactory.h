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
			if (!s_factoryInstance)
			{
				s_factoryInstance = new GraphicsDeviceFactory();
			}

			return s_factoryInstance;
		}

		GraphicsDevice* CreateGraphicsDevice(EGraphicsDeviceType a_type);
		private:
		static GraphicsDeviceFactory* s_factoryInstance;
	};
}
