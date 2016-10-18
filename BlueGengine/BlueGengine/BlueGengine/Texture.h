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

		bool LoadTexture(const char* a_fileName, ImageFormat a_imageFormat, ImageFormat a_formatToStore, uint32 a_mipMapLevel = 0);

		uint32 GetWidth();
		uint32 GetHeight();

		void Bind();
		void UnBind();

		private:
		TextureImpl* m_impl;
	};
}