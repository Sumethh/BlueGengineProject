#include "ElementBuffer.h"
#include "impl/ElementBufferImpl.h"
namespace BlueGengine
{

	ElementBuffer::ElementBuffer()
	{
		//TODO: Make this dependant on the current graphics device we are using!!
		m_impl = new OpenlGlElementBufferImpl();
	}

	ElementBuffer::~ElementBuffer()
	{
		Unload();
		delete m_impl;
	}

	void ElementBuffer::Build()
	{
		m_impl->Build();
	}

	void ElementBuffer::Unload()
	{
		m_impl->Unload();

	}

	void ElementBuffer::SetData(void* a_data, uint32 a_dataSize)
	{
		m_impl->SetData(a_data, a_dataSize);

	}
	void ElementBuffer::Bind()
	{
		m_impl->Bind();
	}

	void ElementBuffer::UnBind()
	{
		m_impl->UnBind();
	}
}