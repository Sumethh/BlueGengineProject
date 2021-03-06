#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include "BlueCore/Core/Log.h"

namespace Blue
{
	IGraphicsDevice* IGraphicsDevice::mCurrentGraphicsDevice = nullptr;

	IGraphicsDevice::IGraphicsDevice(EGraphicsDeviceType aType) :
		mGraphicsType(aType)
	{
		if (mCurrentGraphicsDevice)
		{
			Log::Error("Already a graphics device present");
		}
		else
		{
			mCurrentGraphicsDevice = this;
		}
	}

}