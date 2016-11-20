#pragma once
#include "FrameBuffer.h "
#include "../impl/FrameBufferImpl.h"
namespace BlueGengine
{
	FrameBuffer::FrameBuffer()
	{
		mImpl = new OpenGLFrameBuffer();
	}

	FrameBuffer::~FrameBuffer()
	{
		delete mImpl;
	}

	void FrameBuffer::Bind()
	{
		mImpl->Bind();
	}

	void FrameBuffer::UnBind()
	{
		mImpl->UnBind();

	}

	void FrameBuffer::Clear()
	{
		mImpl->Clear();

	}

	void FrameBuffer::Recreate()
	{
		mImpl->Recreate();

	}
}