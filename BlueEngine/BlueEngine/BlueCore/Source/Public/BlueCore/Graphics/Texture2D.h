#pragma once
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"

namespace Blue
{
	class Texture2D : public NonCopyable
	{
	public:
		Texture2D();
		~Texture2D();

		bool LoadTexture(const char* aFileName, EImageFormat aImageFormat, EPrecisionType FormatToStore, uint32 aMipMapLevel = 0);

		inline uint32 GetWidth() const
		{
			return mWidth;
		}
		inline uint32 GetHeight()const
		{
			return mHeight;
		}

		void Bind();
		void UnBind();
		EImageFormat GetImageFormat()const
		{
			return mImageFormat;
		}
	private:
		GraphicsDeviceResourceID mTextureId;
		uint32 mWidth;
		uint32 mHeight;
		EImageFormat mImageFormat;
	};
}