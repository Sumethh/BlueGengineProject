#include "VertexBufferImpl.h"
#include <gl/glew.h>
#include "../DataDescriptor.h"
#include "../Defines.h"


namespace BlueGengine
{
	OpenlGlVertexBufferImpl::OpenlGlVertexBufferImpl() : mVbo(0)
	{
	}
	OpenlGlVertexBufferImpl::~OpenlGlVertexBufferImpl()
	{
		Unload();
	}

	void OpenlGlVertexBufferImpl::SetData(void* aData, uint32 aDataSize, DataDescriptor* aDescriptors, uint32 aDescriptorCount, bool aMapBuffer)
	{
		if (!mVbo)
		{
			Rebuild();
		}

		Bind();
		glBufferData(GL_ARRAY_BUFFER, aDataSize, aData, GL_DYNAMIC_DRAW);

		for (uint32 i = 0; i < aDescriptorCount; i++)
		{
			DataDescriptor* desc = &aDescriptors[i];

			if (desc != nullptr)
			{
				glEnableVertexAttribArray(desc->location);
				glVertexAttribPointer(desc->location, desc->count, GL_FLOAT, desc->normalized, desc->stride, (void*)desc->offset);
			}

			if (desc->instanced)
			{
				glVertexAttribDivisor(desc->location, desc->instanceCount);
			}

		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void OpenlGlVertexBufferImpl::ReUploadData(void* aData, uint32 aDataSize)
	{
		BlueAssert(mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, aDataSize, aData, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenlGlVertexBufferImpl::Rebuild()
	{
		glGenBuffers(1, &mVbo);
	}

	void OpenlGlVertexBufferImpl::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	}

	void OpenlGlVertexBufferImpl::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	void OpenlGlVertexBufferImpl::Unload()
	{
		if (mVbo)
		{
			glDeleteVertexArrays(1, &mVbo);
		}
	}

	/*
	    void VertexBuffer::BeginMap()
	    {
	    if (!m_mapBufferPtr && m_init)
	    {
	    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	    m_mapBufferPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
	    }
	    }

	    void VertexBuffer::MapData(void* aData, uint32 aDataSize)
	    {
	    if (!m_mapBufferPtr || !m_init)
	    {
	    return;
	    }

	    std::memcpy(m_mapBufferPtr, aData, aDataSize);
	    m_mapBufferPtr = (void*)((char*)m_mapBufferPtr + aDataSize);


	    void VertexBuffer::EndMap()
	    {
	    if (m_mapBufferPtr && m_init)
	    {
	    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	    glUnmapBuffer(GL_ARRAY_BUFFER);
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
	    m_mapBufferPtr = nullptr;

	    }
	    }

	    }
	*/
}