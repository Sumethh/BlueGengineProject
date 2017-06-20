#include "Core/Vertex.h"
#include "Core/Log.h"
#include "Graphics/Mesh.h"
#include "GraphicsDevice/IGraphicsDevice.h"

namespace Blue
{
	Mesh::Mesh(uint64 aId) : mBuffersInit(false), mMeshID(aId)
	{
	}

	Mesh::~Mesh()
	{
		delete mVertices;
		delete mIndices;
		IGraphicsDevice* gd = IGraphicsDevice::GetCurrentGraphicsDevice();
		gd->DeleteGraphicsResource(mVertexArrayId);
		gd->DeleteGraphicsResource(mVertexBufferId);
		gd->DeleteGraphicsResource(mElementBufferId);

	}

	void Mesh::Init(Vertex* aVertexArray, uint32 aVertexCount, uint32* aIndicies, uint32 aIndiceCount)
	{
		SetVertices(aVertexArray, aVertexCount, false);
		SetIndices(aIndicies, aIndiceCount);
	}

	void Mesh::SetVertices(Vertex* aVerticies, uint32 aVertecieCount, bool aCleanUpOldVertecies)
	{
		MarkVerticesForReUpload();

		mVerticeCount = aVertecieCount;

		if (aCleanUpOldVertecies && mVertices)
		{
			delete mVertices;
		}

		mVertices = aVerticies;

	}

	void Mesh::SetIndices(uint32* aIndices, uint32 aIndiceCount, bool aCleanUpOldIndicies)
	{
		MarkIndicesForReUpload();

		mIndiceCount = aIndiceCount;

		if (aCleanUpOldIndicies && mIndices)
		{
			delete mIndices;
		}

		mIndices = aIndices;
	}

	void Mesh::UpdateMeshResources()
	{
		if (!mBuffersInit)
		{
			InitBuffers();
		}

		ReUploadMeshInfo();
	}

	void Mesh::PrepForDrawing()
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->BindGraphicsResource(mVertexArrayId);
	}

	void Mesh::UnPrepForDrawing()
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->UnbindGraphicsResource(mVertexArrayId);
	}

	void Mesh::ReUploadMeshInfo()
	{
		static std::string message = ("ReUploading mesh resources");
		Log::Info(message);

		if (NeedToReuploadVertices())
		{
			BlueAssert(mVertices != nullptr && mVertexBufferId  && mVerticeCount > 0);
			IGraphicsDevice::GetCurrentGraphicsDevice()->UpdateResourceData(mVertexBufferId, 0, (void*)mVertices, sizeof(Vertex) * mVerticeCount);
			ResetFlag(MeshFlags::EReUploadVertices);
		}

		if (NeedToReuploadIndices())
		{
			BlueAssert(mIndices != nullptr && mElementBufferId && mIndiceCount > 0);
			IGraphicsDevice::GetCurrentGraphicsDevice()->UpdateResourceData(mElementBufferId, 0, (void*)mIndices, sizeof(uint32) * mIndiceCount);
			ResetFlag(MeshFlags::EReUploadIndices);
		}

	}

	void Mesh::InitBuffers()
	{
		IGraphicsDevice* gd = IGraphicsDevice::GetCurrentGraphicsDevice();
		mVertexArrayId = gd->CreateGraphicsResource(EGraphicsResourceType::VertexArrayBuffer);
		mVertexBufferId = gd->CreateGraphicsResource(EGraphicsResourceType::VertexBuffer);
		mElementBufferId = gd->CreateGraphicsResource(EGraphicsResourceType::ElementBuffer);
		gd->BindGraphicsResource(mVertexArrayId);
		gd->BindGraphicsResource(mElementBufferId);
		gd->UpdateResourceData(mVertexBufferId, 0, nullptr, 0, sVertexDescriptors, sVertexDescriptorCount);
		gd->UnbindGraphicsResource(mVertexArrayId);
	}
}