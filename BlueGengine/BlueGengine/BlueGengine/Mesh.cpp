#include "Mesh.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Log.h"
namespace BlueGengine
{
	Mesh::Mesh(uint32 a_id) : m_meshID(a_id)
	{
		InitBuffers();
	}

	Mesh::~Mesh()
	{
		delete m_vertices;
		delete m_indices;
		delete m_elementBuffer;
		delete m_vertexArray;
		delete m_vertexBuffer;
	}

	void Mesh::Init(Vertex* a_vertexArray, uint32 a_vertexCount, uint32* a_indicies, uint32 a_indiceCount)
	{
		SetVertices(a_vertexArray, a_vertexCount, false);
		SetIndices(a_indicies, a_indiceCount);
	}

	void Mesh::SetVertices(Vertex* a_verticies, uint32 a_vertecieCount, bool a_cleanUpOldVertecies)
	{
		if (a_vertecieCount > m_verticeCount)
		{
			MarkVerticesForReBuild();
		}
		else
		{
			MarkVerticesForReUpload();
		}
		m_verticeCount = a_vertecieCount;
		if (a_cleanUpOldVertecies && m_vertices)
		{
			delete m_vertices;
		}

		m_vertices = a_verticies;

	}

	void Mesh::SetIndices(uint32* a_indices, uint32 a_indiceCount, bool a_cleanUpOldIndicies)
	{
		if (a_indiceCount > m_indiceCount)
		{
			MarkIndicesForReBuild();
		}
		else
		{
			MarkIndicesForReUpload();
		}
		m_indiceCount = a_indiceCount;

		if (a_cleanUpOldIndicies && m_indices)
		{
			delete m_indices;
		}
		m_indices = a_indices;
	}

	void Mesh::UpdateMeshResources()
	{
		if (NeedToReuploadVertices() || NeedToReuploadIndices())
		{
			ReUploadMeshInfo();
		}
		else if (NeedToRebuildVertices() || NeedToRebuildIndices())
		{
			RebuildGpuResources();
		}
	}

	void Mesh::PrepForDrawing()
	{
		m_vertexArray->Bind();
	}

	void Mesh::UnPrepForDrawing()
	{
		m_vertexArray->UnBind();

	}

	void Mesh::ReUploadMeshInfo()
	{
		LOGI("ReUploading mesh resources");
		if (NeedToReuploadVertices())
		{
			BlueAssert(m_vertices != nullptr && m_vertexBuffer != nullptr && m_verticeCount > 0);
			m_vertexBuffer->ReUploadData(m_vertices, m_verticeCount * sizeof(Vertex));
			ResetFlag(MeshFlags::EReUploadVertices);
		}

		if (NeedToReuploadIndices())
		{
			BlueAssert(m_indices != nullptr && m_elementBuffer != nullptr && m_indiceCount > 0);
			m_elementBuffer->SetData((void*)m_indiceCount, m_indiceCount);
			ResetFlag(MeshFlags::EReUploadIndices);
		}

	}

	void Mesh::RebuildGpuResources()
	{
		LOGI("Rebuild mesh gpu resources");
		//Unload my 3 buffers
		m_vertexBuffer->Unload();
		m_elementBuffer->Unload();
		m_vertexArray->Unload();

		//Rebuild the buffers with the new data
		m_vertexArray->Build();
		m_elementBuffer->Build();
		m_elementBuffer->SetData((void*)m_indices, m_indiceCount * sizeof(m_indiceCount));
		m_vertexArray->Bind();
		m_elementBuffer->Bind();
		m_vertexBuffer->SetData((void*)m_vertices, sizeof(Vertex) * m_verticeCount, s_vertexDescriptors, s_vertexDescriptorCount);
		m_vertexArray->UnBind();

		ResetFlag(MeshFlags::ERebuildVerticesResource);
		ResetFlag(MeshFlags::ERebuildIndicesResource);
	}



	void Mesh::InitBuffers()
	{
		m_vertexBuffer = new VertexBuffer();
		m_elementBuffer = new ElementBuffer();
		m_vertexArray = new VertexArray();
	}

}