#pragma once
#include "../Log.h"
#include "../Types.h"
namespace BlueGengine
{
	class FrameBufferImpl
	{
		public:
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void Clear() = 0;
		virtual void Recreate() = 0;

	};

	class OpenGLFrameBuffer : public FrameBufferImpl
	{
		public:
		OpenGLFrameBuffer();
		~OpenGLFrameBuffer();
		virtual void Recreate() override ;
		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void Clear()override;

		uint32 mFB, mPosition, mNormal, mColorSpec;

		private:
		void CreateColorBuffers();
	};
}