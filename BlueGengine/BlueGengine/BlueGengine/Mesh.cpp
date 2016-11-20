#include "Mesh.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Log.h"
namespace BlueGengine
{
	Mesh::Mesh(uint64 aId) : mMeshID(aId)
	{
		InitBuffers();
	}

	Mesh::~Mesh()
	{
		delete mVertices;
		delete mIndices;
		delete mElementBuffer;
		delete mVertexArray;
		delete mVertexBuffer;
	}

	void Mesh::Init(Vertex* aVertexArray, uint32 aVertexCount, uint32* aIndicies, uint32 aIndiceCount)
	{
		SetVertices(aVertexArray, aVertexCount, false);
		SetIndices(aIndicies, aIndiceCount);
	}

	void Mesh::SetVertices(Vertex* aVerticies, uint32 aVertecieCount, bool aCleanUpOldVertecies)
	{
		if (aVertecieCount > mVerticeCount)
		{
			MarkVerticesForReBuild();
		}
		else
		{
			MarkVerticesForReUpload();
		}

		mVerticeCount = aVertecieCount;

		if (aCleanUpOldVertecies && mVertices)
		{
			delete mVertices;
		}

		mVertices = aVerticies;

	}

	void Mesh::SetIndices(uint32* aIndices, uint32 aIndiceCount, bool aCleanUpOldIndicies)
	{
		if (aIndiceCount > mIndiceCount)
		{
			MarkIndicesForReBuild();
		}
		else
		{
			MarkIndicesForReUpload();
		}

		mIndiceCount = aIndiceCount;

		if (aCleanUpOldIndicies && mIndices)
		{
			delete mIndices;
		}

		mIndices = aIndices;
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
		mVertexArray->Bind();
	}

	void Mesh::UnPrepForDrawing()
	{
		mVertexArray->UnBind();

	}

	void Mesh::ReUploadMeshInfo()
	{
		LOGI("ReUploading mesh resources");

		if (NeedToReuploadVertices())
		{
			BlueAssert(mVertices != nullptr && mVertexBuffer != nullptr && mVerticeCount > 0);
			mVertexBuffer->ReUploadData(mVertices, mVerticeCount * sizeof(Vertex));
			ResetFlag(MeshFlags::EReUploadVertices);
		}

		if (NeedToReuploadIndices())
		{
			BlueAssert(mIndices != nullptr && mElementBuffer != nullptr && mIndiceCount > 0);
			mElementBuffer->SetData(mIndices, mIndiceCount);
			ResetFlag(MeshFlags::EReUploadIndices);
		}

	}

	void Mesh::RebuildGpuResources()
	{
		LOGI("Rebuild mesh gpu resources");
		//Unload my 3 buffers
		mVertexBuffer->Unload();
		mElementBuffer->Unload();
		mVertexArray->Unload();

		//Rebuild the buffers with the new data
		mVertexArray->Build();
		mElementBuffer->Build();
		mElementBuffer->SetData(mIndices, mIndiceCount * sizeof(mIndiceCount));
		mVertexArray->Bind();
		mElementBuffer->Bind();
		mVertexBuffer->SetData((void*)mVertices, sizeof(Vertex) * mVerticeCount, sVertexDescriptors, sVertexDescriptorCount);
		mVertexArray->UnBind();

		ResetFlag(MeshFlags::ERebuildVerticesResource);
		ResetFlag(MeshFlags::ERebuildIndicesResource);
	}



	void Mesh::InitBuffers()
	{
		mVertexBuffer = new VertexBuffer();
		mElementBuffer = new ElementBuffer();
		mVertexArray = new VertexArray();
	}

}