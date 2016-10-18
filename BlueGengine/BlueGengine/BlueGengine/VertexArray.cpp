#include "VertexArray.h"
#include "impl/VertexArrayImpl.h"
namespace BlueGengine
{
	VertexArray::VertexArray()
	{
		//if current graphics system is openlgl
		m_impl = new OpenGLVertexArrayImpl();
	}

	VertexArray::~VertexArray()
	{
		delete m_impl;
	}

	void VertexArray::Build()
	{
		m_impl->Build();
	}

	void VertexArray::Bind()
	{
		m_impl->Bind();
	}
	void VertexArray::UnBind()
	{
		m_impl->UnBind();
	}

	void VertexArray::Unload()
	{
		m_impl->Unload();
	}

}