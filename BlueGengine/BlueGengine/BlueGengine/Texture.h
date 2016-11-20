#pragma once
#include "Types.h"
#include "NonCopyable.h"
#include "ImageFormat.h"
namespace BlueGengine
{
	class TextureImpl;
	class Texture : public NonCopyable
	{
		public:
		Texture();
		~Texture();

		bool LoadTexture(const char* aFileName, ImageFormat aImageFormat, ImageFormat aFormatToStore, uint32 aMipMapLevel = 0);

		uint32 GetWidth();
		uint32 GetHeight();

		void Bind();
		void UnBind();

		private:
		TextureImpl* mImpl;
	};
}