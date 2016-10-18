#include "ElementBufferImpl.h"
#include <gl/glew.h>
namespace BlueGengine
{

	OpenlGlElementBufferImpl::OpenlGlElementBufferImpl() : m_ebo(0)
	{
		Build();
	}

	OpenlGlElementBufferImpl::~OpenlGlElementBufferImpl()
	{
		Unload();
	}

	void OpenlGlElementBufferImpl::Build()
	{
		glGenBuffers(1, &m_ebo);

	}

	void OpenlGlElementBufferImpl::Unload()
	{
		if (m_ebo)
		{
			glDeleteBuffers(1, &m_ebo);
		}
	}

	void OpenlGlElementBufferImpl::SetData(void* a_data, uint32 a_dataSize)
	{
		if (!m_ebo)
		{
			Build();
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_dataSize, a_data, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void OpenlGlElementBufferImpl::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	}

	void OpenlGlElementBufferImpl::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

}