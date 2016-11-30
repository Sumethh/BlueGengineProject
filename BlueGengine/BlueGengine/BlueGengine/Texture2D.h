#pragma once
#include "Types.h"
#include "NonCopyable.h"
#include "ImageFormat.h"
namespace BlueGengine
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