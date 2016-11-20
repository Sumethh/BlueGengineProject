#include "ElementBuffer.h"
#include "impl/ElementBufferImpl.h"
namespace BlueGengine
{

	ElementBuffer::ElementBuffer()
	{
		//TODO: Make this dependant on the current graphics device we are using!!
		mImpl = new OpenlGlElementBufferImpl();
	}

	ElementBuffer::~ElementBuffer()
	{
		Unload();
		delete mImpl;
	}

	void ElementBuffer::Build()
	{
		mImpl->Build();
	}

	void ElementBuffer::Unload()
	{
		mImpl->Unload();

	}

	void ElementBuffer::SetData(uint32* aData, uint32 aDataSize)
	{
		mImpl->SetData(aData, aDataSize);

	}
	void ElementBuffer::Bind()
	{
		mImpl->Bind();
	}

	void ElementBuffer::UnBind()
	{
		mImpl->UnBind();
	}
}