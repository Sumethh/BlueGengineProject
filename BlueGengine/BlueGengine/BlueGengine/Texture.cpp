#include "Texture.h"
#include <gl/glew.h>
#include <FreeImage/FreeImage.h>
#include "Log.h"
#include "Defines.h"
#include "impl/TextureImpl.h"
namespace BlueGengine
{
	Texture::~Texture()
	{
		delete m_impl;
	}

	Texture::Texture()
	{
		m_impl = new OpenGLTexture();
	}

	bool Texture::LoadTexture(const char* a_fileName, ImageFormat a_imageFormat, ImageFormat a_formatToStore, uint32 a_mipMapLvl)
	{
		return m_impl->LoadTexture(a_fileName, a_imageFormat, a_formatToStore, a_mipMapLvl);
	}


	uint32 Texture::GetWidth()
	{
		return m_impl->GetWidth();
	}

	uint32 Texture::GetHeight()
	{
		return m_impl->GetHeight();
	}

	void Texture::Bind()
	{
		m_impl->Bind();
	}

	void Texture::UnBind()
	{
		m_impl->UnBind();
	}

}