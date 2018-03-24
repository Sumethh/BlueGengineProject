#include "BlueCore/Graphics/Texture2D.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Tasks/UpdateGraphicsResourceTask.h"

#include <FreeImage/FreeImage.h>
#include <gl/glew.h>

namespace Blue
{
	Texture2D::Texture2D()
	{
	}

	Texture2D::~Texture2D()
	{
	}

	void Texture2D::Create()
	{
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();
		mGraphicsResource = device->CreateGraphicsResource(EGraphicsResourceType::Texture2D);
	}

	void Texture2D::UpdateResource()
	{
		BlueAssert(mCurrentBitMap);
		IGraphicsDevice* graphicsDevice = IGraphicsDevice::GetCurrentGraphicsDevice();
		graphicsDevice->UpdateResourceData(mGraphicsResource, FreeImage_GetBits(mCurrentBitMap), mWidth, mHeight, mPrecision, mImageFormat, EDataType::UnsignedByte, mMipLevel);
		FreeImage_Unload(mCurrentBitMap);
		mCurrentBitMap = nullptr;
	}

	bool Texture2D::LoadTexture(const char* aFileName, EImageFormat aImageFormat, EColorPrecisionType aFormatToStore, uint32 aMipMapLvl)
	{		
		mImageFormat = aImageFormat;

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

		FIBITMAP* dib(0);
		ubyte* bits(0);
		uint32 width(0), height(0);

		fif = FreeImage_GetFileType(aFileName);

		if (fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(aFileName);
		}

		if (fif == FIF_UNKNOWN)
		{
			Log::Error("Unkown file type when trying to load texture");
			return false;
		}

		if (FreeImage_FIFSupportsReading(fif))
		{
			dib = FreeImage_Load(fif, aFileName);
		}

		if (!dib)
		{
			BlueAssert(dib != nullptr);
			return false;
		}

		bits = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);


		mCurrentBitMap = dib;
		mWidth = width;
		mHeight = height;
		mMipLevel = aMipMapLvl;
		mPrecision = aFormatToStore;

		UpdateGraphicsResourceTask* updateResourceTask = new UpdateGraphicsResourceTask();
		updateResourceTask->graphicsResourceToUpdate = this;
		TaskSystem::SubmitTask(updateResourceTask);

		return true;
	}

	void Texture2D::Bind(ETextureID aId)
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->BindGraphicsResource(mGraphicsResource, aId);
	}
}