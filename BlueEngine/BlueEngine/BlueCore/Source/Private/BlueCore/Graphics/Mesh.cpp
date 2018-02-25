#include "BlueCore/Core/Vertex.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Graphics/Mesh.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"

namespace Blue
{
	Mesh::Mesh(uint64 aId) : mBuffersInit(false), mMeshID(aId)
	{
	}

	Mesh::~Mesh()
	{
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();
		if(mVertexBufferId)
			device->DeleteGraphicsResource(mVertexBufferId);
		if(mElementBufferId)
			device->DeleteGraphicsResource(mElementBufferId);
	}

	void Mesh::Create()
	{
		InitBuffers();
	}

	void Mesh::UpdateResource()
	{
		UpdateMeshResources();
	}

	void Mesh::Init(Vertex* aVertexArray, uint32 aVertexCount, uint32* aIndicies, uint32 aIndiceCount)
	{
		if (!IsValid())
			Create();
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
		BlueAssert(IsValid());
		ReuploadMeshInfo();
	}

	void Mesh::ReuploadMeshInfo()
	{
		static std::string message = ("ReUploading mesh resources ID: ");
		Log::Info(Logger(message) << mGraphicsResource);

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
		mGraphicsResource = gd->CreateGraphicsResource(EGraphicsResourceType::VertexArrayBuffer);
		mVertexBufferId = gd->CreateGraphicsResource(EGraphicsResourceType::VertexBuffer);
		mElementBufferId = gd->CreateGraphicsResource(EGraphicsResourceType::ElementBuffer);

		Bind();
		gd->BindGraphicsResource(mElementBufferId);
		gd->UpdateResourceData(mVertexBufferId, 0, nullptr, 0, sVertexDescriptors, sVertexDescriptorCount);
		Unbind();
		mBuffersInit = true;
	}
}