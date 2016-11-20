#include "TextureImpl.h"

#include <gl/glew.h>
#include <FreeImage/FreeImage.h>
#include "../Log.h"
#include "../Defines.h"
namespace BlueGengine
{
	OpenGLTexture::~OpenGLTexture()
	{
		if (mTextureHandle)
		{
			glDeleteTextures(1, &mTextureHandle);
		}
	}

	OpenGLTexture::OpenGLTexture() :
	mTextureHandle(0)
	{

	}

	bool OpenGLTexture::LoadTexture(const char* aFileName, ImageFormat aImageFormat, ImageFormat aFormatToStore, uint32 aMipMapLvl)
	{

		uint32 imageFormat, storingFormat;

		if (aImageFormat == ImageFormat::IF_RGB)
		{
			imageFormat = GL_RGB;
		}
		else
		{
			imageFormat = GL_RGBA;
		}

		if (aFormatToStore == ImageFormat::IF_RGB)
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

		fif = FreeImage_GetFileType(aFileName);

		if (fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(aFileName);
		}

		if (fif == FIF_UNKNOWN)
		{
			std::cout << "Unkown file type when trying to load texture" << std::endl;
			return nullptr;
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



		glGenTextures(1, &glTexID);

		glBindTexture(GL_TEXTURE_2D, glTexID);
		glTexImage2D(GL_TEXTURE_2D, aMipMapLvl, imageFormat, width, height, 0, storingFormat, GL_UNSIGNED_BYTE, bits);
		glGenerateMipmap(GL_TEXTURE_2D);
		FreeImage_Unload(dib);

		mTextureHandle = glTexID;
		/*  SetWidth(width);
		    SetHeight(height);*/
		m_width = width;
		m_height = height;
		return true;
	}


	void OpenGLTexture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, mTextureHandle);
	}

	void OpenGLTexture::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}