#pragma once
#include "VertexBuffer.h"
#include "impl/VertexBufferImpl.h"
namespace BlueGengine
{
	VertexBuffer::VertexBuffer() :
	mImpl(nullptr)
	{
		//TODO: Make this Dependant on the graphics device we are currently using!
		mImpl = new OpenlGlVertexBufferImpl();
	}

	VertexBuffer::~VertexBuffer()
	{
		Unload();
		delete mImpl;
	}

	void VertexBuffer::SetData(void* aData, uint32 aDataSize, DataDescriptor* aDescriptors, uint32 aDescriptorCount, bool aMapBuffer)
	{
		mImpl->SetData(aData, aDataSize, aDescriptors, aDescriptorCount, aMapBuffer);
	}

	void VertexBuffer::ReUploadData(void* aData, uint32 aDataSize)
	{
		mImpl->ReUploadData(aData, aDataSize);
	}

	void VertexBuffer::Unload()
	{
		mImpl->Unload();
	}

	void VertexBuffer::Bind()
	{
		mImpl->Bind();
	}

	void VertexBuffer::UnBind()
	{
		mImpl->UnBind();
	}

}