#pragma once
#include "VertexBuffer.h"
#include "impl/VertexBufferImpl.h"
namespace BlueGengine
{
	VertexBuffer::VertexBuffer() :
	m_impl(nullptr)
	{
		//TODO: Make this Dependant on the graphics device we are currently using!
		m_impl = new OpenlGlVertexBufferImpl();
	}

	VertexBuffer::~VertexBuffer()
	{
		Unload();
		delete m_impl;
	}

	void VertexBuffer::SetData(void* a_data, uint32 a_dataSize, DataDescriptor* a_descriptors, uint32 a_descriptorCount, bool a_mapBuffer)
	{
		m_impl->SetData(a_data, a_dataSize, a_descriptors, a_descriptorCount, a_mapBuffer);
	}

	void VertexBuffer::ReUploadData(void* a_data, uint32 a_dataSize)
	{
		m_impl->ReUploadData(a_data, a_dataSize);
	}

	void VertexBuffer::Unload()
	{
		m_impl->Unload();
	}

	void VertexBuffer::Bind()
	{
		m_impl->Bind();
	}

	void VertexBuffer::UnBind()
	{
		m_impl->UnBind();
	}

}