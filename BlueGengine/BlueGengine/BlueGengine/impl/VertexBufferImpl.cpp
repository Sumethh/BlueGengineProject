#include "VertexBufferImpl.h"
#include <gl/glew.h>
#include "../DataDescriptor.h"
#include "../Defines.h"


namespace BlueGengine
{
	OpenlGlVertexBufferImpl::OpenlGlVertexBufferImpl() : m_vbo(0)
	{
		Rebuild();
	}
	OpenlGlVertexBufferImpl::~OpenlGlVertexBufferImpl()
	{
		Unload();
	}

	void OpenlGlVertexBufferImpl::SetData(void* a_data, uint32 a_dataSize, DataDescriptor* a_descriptors, uint32 a_descriptorCount, bool a_mapBuffer)
	{
		if (!m_vbo)
		{
			Rebuild();
		}
		Bind();
		glBufferData(GL_ARRAY_BUFFER, a_dataSize, a_data, GL_DYNAMIC_DRAW);
		for (int i = 0; i < a_descriptorCount; i++)
		{
			DataDescriptor* desc = &a_descriptors[i];

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

	void OpenlGlVertexBufferImpl::ReUploadData(void* a_data, uint32 a_dataSize)
	{
		BlueAssert(m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, a_dataSize, a_data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenlGlVertexBufferImpl::Rebuild()
	{
		glGenBuffers(1, &m_vbo);
	}

	void OpenlGlVertexBufferImpl::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}

	void OpenlGlVertexBufferImpl::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	void OpenlGlVertexBufferImpl::Unload()
	{
		if (m_vbo)
		{
			glDeleteVertexArrays(1, &m_vbo);
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

	    void VertexBuffer::MapData(void* a_data, uint32 a_dataSize)
	    {
	    if (!m_mapBufferPtr || !m_init)
	    {
	    return;
	    }

	    std::memcpy(m_mapBufferPtr, a_data, a_dataSize);
	    m_mapBufferPtr = (void*)((char*)m_mapBufferPtr + a_dataSize);


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