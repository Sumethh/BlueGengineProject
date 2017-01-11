#include "GraphicsDevice/GraphicsDeviceFactory.h"
#include "GraphicsDevice/IGraphicsDevice.h"
#include "GraphicsDevice/OpenGlGraphicsDevice.h"

namespace BlueCore
{
	GraphicsDeviceFactory* GraphicsDeviceFactory::sFactoryInstance;
	GraphicsDeviceFactory::GraphicsDeviceFactory()
	{

	}

	IGraphicsDevice* GraphicsDeviceFactory::CreateGraphicsDevice(EGraphicsDeviceType a_type)
	{
		switch (a_type)
		{
			case BlueCore::EGraphicsDeviceType::OpenGL:
				return new OpenGlGraphicsDevice();
				break;

			case BlueCore::EGraphicsDeviceType::Vulkan:
				BlueAssert(false);
				break;

			case BlueCore::EGraphicsDeviceType::D3D11:
				BlueAssert(false);

				break;

			case BlueCore::EGraphicsDeviceType::D3D12:
				BlueAssert(false);

				break;

			case BlueCore::EGraphicsDeviceType::UnIdentified:
				BlueAssert(false);

				break;

			default:
				BlueAssert(false);

				break;
		}

		return nullptr;
	}
}