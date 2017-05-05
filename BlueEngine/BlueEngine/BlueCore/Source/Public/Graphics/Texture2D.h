#pragma once
#include "Core/Types.h"
#include "Core/NonCopyable.h"
#include "Graphics/EImageFormat.h"

class Texture2D : public NonCopyable
{
	public:
	Texture2D();
	~Texture2D();

	bool LoadTexture(const char* aFileName, EImageFormat aImageFormat, EImageFormat aFormatToStore, uint32 aMipMapLevel = 0);

	inline uint32 GetWidth() const { return mWidth; }
	inline uint32 GetHeight()const { return mHeight; }

	void Bind();
	void UnBind();
	EImageFormat GetImageFormat()const { return mImageFormat; }
	private:
	uint32 mTextureId;
	uint32 mWidth;
	uint32 mHeight;
	EImageFormat mImageFormat;
};
