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
		delete mImpl;
	}

	Texture::Texture()
	{
		mImpl = new OpenGLTexture();
	}

	bool Texture::LoadTexture(const char* aFileName, ImageFormat aImageFormat, ImageFormat aFormatToStore, uint32 aMipMapLvl)
	{
		return mImpl->LoadTexture(aFileName, aImageFormat, aFormatToStore, aMipMapLvl);
	}


	uint32 Texture::GetWidth()
	{
		return mImpl->GetWidth();
	}

	uint32 Texture::GetHeight()
	{
		return mImpl->GetHeight();
	}

	void Texture::Bind()
	{
		mImpl->Bind();
	}

	void Texture::UnBind()
	{
		mImpl->UnBind();
	}

}