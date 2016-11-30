#include "Texture2D.h"
#include <gl/glew.h>
#include <FreeImage/FreeImage.h>
#include "Log.h"
#include "Defines.h"
#include "Graphics/IGraphicsDevice.h"
namespace BlueGengine
{
	Texture2D::Texture2D() : mTextureId(0)
	{
	}

	Texture2D::~Texture2D()
	{
	}


	bool Texture2D::LoadTexture(const char* aFileName, ImageFormat aImageFormat, ImageFormat aFormatToStore, uint32 aMipMapLvl)
	{
		IGraphicsDevice* gd = IGraphicsDevice::GetCurrentGraphicsDevice();

		if (mTextureId == 0)
		{
			mTextureId = gd->CreateGraphicsResource(EGraphicsResourceType::Texture2D);
		}

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
			Log::LogError("Unkown file type when trying to load texture");
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

		BlueAssert(bits != nullptr);
		BlueAssert(width != 0);
		BlueAssert(height != 0);

		gd->UpdateResourceData(mTextureId, bits, width, height, aImageFormat, aFormatToStore, aMipMapLvl);
		FreeImage_Unload(dib);

		mWidth = width;
		mHeight = height;
		return true;
	}

	void Texture2D::Bind()
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->BindGraphicsResource(mTextureId);
	}

	void Texture2D::UnBind()
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->UnBindGraphicsResource(mTextureId);
	}

}