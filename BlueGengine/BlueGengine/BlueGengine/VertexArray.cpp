#include "VertexArray.h"
#include "impl/VertexArrayImpl.h"
namespace BlueGengine
{
	VertexArray::VertexArray()
	{
		//if current graphics system is openlgl
		mImpl = new OpenGLVertexArrayImpl();
	}

	VertexArray::~VertexArray()
	{
		delete mImpl;
	}

	void VertexArray::Build()
	{
		mImpl->Build();
	}

	void VertexArray::Bind()
	{
		mImpl->Bind();
	}
	void VertexArray::UnBind()
	{
		mImpl->UnBind();
	}

	void VertexArray::Unload()
	{
		mImpl->Unload();
	}

}