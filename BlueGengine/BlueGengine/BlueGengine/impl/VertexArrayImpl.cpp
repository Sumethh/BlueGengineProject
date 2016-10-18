#include "VertexArrayImpl.h"
#include <gl/glew.h>

namespace BlueGengine
{
	OpenGLVertexArrayImpl::OpenGLVertexArrayImpl() : m_vao(0)
	{
		Build();
	}
	OpenGLVertexArrayImpl::~OpenGLVertexArrayImpl()
	{
		Unload();
	}

	void OpenGLVertexArrayImpl::Build()
	{
		glGenVertexArrays(1, &m_vao);
	}

	void OpenGLVertexArrayImpl::Bind()
	{
		glBindVertexArray(m_vao);
	}

	void OpenGLVertexArrayImpl::UnBind()
	{
		glBindVertexArray(0);
	}


	void OpenGLVertexArrayImpl::Unload()
	{
		glDeleteVertexArrays(1, &m_vao);
	}

}