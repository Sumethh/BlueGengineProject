#include "IGraphicsDevice.h"
#include "../Log.h"
namespace BlueGengine
{
	IGraphicsDevice* IGraphicsDevice::mCurrentGraphicsDevice = nullptr;

	IGraphicsDevice::IGraphicsDevice(EGraphicsDeviceType aType) :
	mGraphicsType(aType)
	{
		if (mCurrentGraphicsDevice)
		{
			Log::LogError("Already a graphics device present");
		}
		else
		{
			mCurrentGraphicsDevice = this;
		}
	}
}