#include "GraphicsDevice/IGraphicsDevice.h"
#include "Core/Log.h"
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