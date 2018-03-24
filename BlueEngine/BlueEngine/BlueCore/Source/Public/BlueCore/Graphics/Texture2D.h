#pragma once
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include "BlueCore/Graphics/GraphicsResource.h"


struct FIBITMAP;
namespace Blue
{
	class Texture2D : public NonCopyable, public GraphicsResource
	{
	public:
		Texture2D();
		~Texture2D();

		virtual void Create() override;
		virtual void UpdateResource() override;

		bool LoadTexture(const char* aFileName, EImageFormat aImageFormat, EColorPrecisionType FormatToStore, uint32 aMipMapLevel = 0);

		inline uint32 GetWidth() const
		{
			return mWidth;
		}
		inline uint32 GetHeight()const
		{
			return mHeight;
		}

		void Bind(ETextureID aId = ETextureID::Texture0);

		EImageFormat GetImageFormat()const
		{
			return mImageFormat;
		}

	private:
		uint32 mWidth;
		uint32 mHeight;
		EImageFormat mImageFormat;
		EColorPrecisionType mPrecision;
		uint32 mMipLevel;
		FIBITMAP* mCurrentBitMap;
	};
}