#include "GraphicsDeviceFactory.h"
#include "IGraphicsDevice.h"
#include "OpenGlGraphicsDevice.h"

namespace BlueGengine
{
	GraphicsDeviceFactory* GraphicsDeviceFactory::sFactoryInstance;
	GraphicsDeviceFactory::GraphicsDeviceFactory()
	{

	}

	IGraphicsDevice* GraphicsDeviceFactory::CreateGraphicsDevice(EGraphicsDeviceType a_type)
	{
		switch (a_type)
		{
			case BlueGengine::EGraphicsDeviceType::OpenGL:
				return new OpenGlGraphicsDevice();
				break;

			case BlueGengine::EGraphicsDeviceType::Vulkan:
				BlueAssert(false);
				break;

			case BlueGengine::EGraphicsDeviceType::D3D11:
				BlueAssert(false);

				break;

			case BlueGengine::EGraphicsDeviceType::D3D12:
				BlueAssert(false);

				break;

			case BlueGengine::EGraphicsDeviceType::UnIdentified:
				BlueAssert(false);

				break;

			default:
				BlueAssert(false);

				break;
		}

		return nullptr;
	}
}