#include "ElementBufferImpl.h"
#include <gl/glew.h>
namespace BlueGengine
{

	OpenlGlElementBufferImpl::OpenlGlElementBufferImpl() : mEbo(0)
	{
		Build();
	}

	OpenlGlElementBufferImpl::~OpenlGlElementBufferImpl()
	{
		Unload();
	}

	void OpenlGlElementBufferImpl::Build()
	{
		glGenBuffers(1, &mEbo);

	}

	void OpenlGlElementBufferImpl::Unload()
	{
		if (mEbo)
		{
			glDeleteBuffers(1, &mEbo);
		}
	}

	void OpenlGlElementBufferImpl::SetData(uint32* aData, uint32 aDataSize)
	{
		if (!mEbo)
		{
			Build();
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, aDataSize, (void*)aData, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void OpenlGlElementBufferImpl::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);

	}

	void OpenlGlElementBufferImpl::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

}