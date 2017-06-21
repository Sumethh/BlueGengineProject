#include "BlueCore/GraphicsDevice/GraphicsDeviceFactory.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include "BlueCore/GraphicsDevice/OpenGlGraphicsDevice.h"

namespace Blue
{
	GraphicsDeviceFactory* GraphicsDeviceFactory::sFactoryInstance;
	GraphicsDeviceFactory::GraphicsDeviceFactory()
	{

	}

	IGraphicsDevice* GraphicsDeviceFactory::CreateGraphicsDevice(EGraphicsDeviceType a_type)
	{
		switch (a_type)
		{
			case EGraphicsDeviceType::OpenGL:
				return new OpenGlGraphicsDevice();
				break;

			case EGraphicsDeviceType::Vulkan:
				BlueAssert(false);
				break;

			case EGraphicsDeviceType::D3D11:
				BlueAssert(false);

				break;

			case EGraphicsDeviceType::D3D12:
				BlueAssert(false);

				break;

			case EGraphicsDeviceType::UnIdentified:
				BlueAssert(false);

				break;

			default:
				BlueAssert(false);

				break;
		}

		return nullptr;
	}
}