#include "VertexArrayImpl.h"
#include <gl/glew.h>

namespace BlueGengine
{
	OpenGLVertexArrayImpl::OpenGLVertexArrayImpl() : mVao(0)
	{
		Build();
	}
	OpenGLVertexArrayImpl::~OpenGLVertexArrayImpl()
	{
		Unload();
	}

	void OpenGLVertexArrayImpl::Build()
	{
		glGenVertexArrays(1, &mVao);
	}

	void OpenGLVertexArrayImpl::Bind()
	{
		glBindVertexArray(mVao);
	}

	void OpenGLVertexArrayImpl::UnBind()
	{
		glBindVertexArray(0);
	}


	void OpenGLVertexArrayImpl::Unload()
	{
		glDeleteVertexArrays(1, &mVao);
	}

}