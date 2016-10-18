#pragma once
#include "../Types.h"
#include "../ImageFormat.h"
namespace BlueGengine
{
	class TextureImpl
	{
		public:
		TextureImpl() {};
		virtual ~TextureImpl() {};
		virtual bool LoadTexture(const char* a_fileName, ImageFormat a_imageFormat, ImageFormat a_formatToStore, uint32 a_mipMapLevel = 0) = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		inline uint32 GetWidth() const { return m_width; }
		inline uint32 GetHeight() const { return m_height; }
		protected:
		uint32 m_width;
		uint32 m_height;
	};



	class OpenGLTexture : public TextureImpl
	{
		public:
		OpenGLTexture();
		~OpenGLTexture();
		virtual bool LoadTexture(const char* a_fileName, ImageFormat a_imageFormat, ImageFormat a_formatToStore, uint32 a_mipMapLevel = 0);

		virtual void Bind();
		virtual void UnBind();
		private:
		uint32 m_textureHandle;
	};

}
