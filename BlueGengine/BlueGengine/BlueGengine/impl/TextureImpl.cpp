#include "TextureImpl.h"

#include <gl/glew.h>
#include <FreeImage/FreeImage.h>
#include "../Log.h"
#include "../Defines.h"
namespace BlueGengine
{
	OpenGLTexture::~OpenGLTexture()
	{
		if (m_textureHandle)
		{
			glDeleteTextures(1, &m_textureHandle);
		}
	}

	OpenGLTexture::OpenGLTexture() :
	m_textureHandle(0)
	{

	}

	bool OpenGLTexture::LoadTexture(const char* a_fileName, ImageFormat a_imageFormat, ImageFormat a_formatToStore, uint32 a_mipMapLvl)
	{

		uint32 imageFormat, storingFormat;

		if (a_imageFormat == ImageFormat::IF_RGB)
		{
			imageFormat = GL_RGB;
		}
		else
		{
			imageFormat = GL_RGBA;
		}

		if (a_formatToStore == ImageFormat::IF_RGB)
		{
			storingFormat = GL_RGB;
		}
		else
		{
			storingFormat = GL_RGBA;
		}

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

		FIBITMAP* dib(0);
		BYTE* bits(0);
		uint32 width(0), height(0);
		uint32 glTexID;

		fif = FreeImage_GetFileType(a_fileName);

		if (fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(a_fileName);
		}

		if (fif == FIF_UNKNOWN)
		{
			std::cout << "Unkown file type when trying to load texture" << std::endl;
			return nullptr;
		}

		if (FreeImage_FIFSupportsReading(fif))
		{
			dib = FreeImage_Load(fif, a_fileName);
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



		glGenTextures(1, &glTexID);

		glBindTexture(GL_TEXTURE_2D, glTexID);
		glTexImage2D(GL_TEXTURE_2D, a_mipMapLvl, imageFormat, width, height, 0, storingFormat, GL_UNSIGNED_BYTE, bits);
		glGenerateMipmap(GL_TEXTURE_2D);
		FreeImage_Unload(dib);

		m_textureHandle = glTexID;
		/*  SetWidth(width);
		    SetHeight(height);*/
		m_width = width;
		m_height = height;
		return true;
	}


	void OpenGLTexture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
	}

	void OpenGLTexture::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}