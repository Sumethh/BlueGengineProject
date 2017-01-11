#pragma once
#include "Core/Types.h"
#include "Core/NonCopyable.h"
#include "Graphics/ImageFormat.h"
namespace BlueCore
{

	class Texture2D : public NonCopyable
	{
		public:
		Texture2D();
		~Texture2D();

		bool LoadTexture(const char* aFileName, ImageFormat aImageFormat, ImageFormat aFormatToStore, uint32 aMipMapLevel = 0);

		inline uint32 GetWidth() const { return mWidth; }
		inline uint32 GetHeight()const { return mHeight; }

		void Bind();
		void UnBind();

		private:
		uint32 mTextureId;
		uint32 mWidth;
		uint32 mHeight;
	};
}