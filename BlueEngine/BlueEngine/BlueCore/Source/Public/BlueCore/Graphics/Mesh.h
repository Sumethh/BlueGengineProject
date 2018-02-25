#pragma once

#include "BlueCore/Core/Vertex.h"
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Core/CapturedPrimitiveData.h"

#include "BlueCore/Graphics/GraphicsResource.h"

#include <vector>
#include <glm/glm.hpp>

namespace Blue
{
	class Mesh : public GraphicsResource
	{
	private:
		enum MeshFlags
		{
			EReUploadVertices = BlueBit(0),
			EReUploadIndices = BlueBit(1)
		};
	public:

		Mesh(uint64 aId);
		~Mesh();

		virtual void Create() override;
		virtual void UpdateResource() override;

		void Init(Vertex* aVertexArray, uint32 aVertexCount, uint32* aIndices, uint32 aIndiceCount);

		inline Vertex* GetVertices() const
		{
			return mVertices;
		}
		inline uint32 GetVerticeCount() const
		{
			return mVerticeCount;
		}

		inline uint32 GetIndiceCount()const
		{
			return mIndiceCount;
		}
		inline uint32* GetIndices() const
		{
			return mIndices;
		}

		void SetVertices(Vertex* aVertices, uint32 aVerticeCount, bool aCleanUpOldVertecies = true);
		void SetIndices(uint32* aIndices, uint32 aIndiceCount, bool aCleanUpOldIndicies = true);

		inline void MarkVerticesForReUpload()
		{
			mMeshFlags |= MeshFlags::EReUploadVertices;
		}
		inline void MarkIndicesForReUpload()
		{
			mMeshFlags |= MeshFlags::EReUploadIndices;
		}

		inline bool NeedToReuploadIndices()const
		{
			return (mMeshFlags & MeshFlags::EReUploadIndices) > 0;
		}
		inline bool NeedToReuploadVertices()const
		{
			return (mMeshFlags & MeshFlags::EReUploadVertices) > 0;
		}

		void UpdateMeshResources();

		inline void CaptureData(CapturedPrimitiveData& aCapturedData) const
		{
			aCapturedData.meshResourceToBind = mGraphicsResource;
			aCapturedData.vertexCount = mVerticeCount;
			aCapturedData.indexCount = mIndiceCount;
		}

		uint64 GetID() const
		{
			return mMeshID;
		}

	private:
		inline void ResetFlag(MeshFlags aFlag)
		{
			mMeshFlags &= ~aFlag;
		}
		void ReuploadMeshInfo();
		void InitBuffers();

		bool mBuffersInit;

		GraphicsDeviceResourceID mVertexBufferId = 0;
		GraphicsDeviceResourceID mElementBufferId = 0;

		Vertex* mVertices = nullptr;
		uint32 mVerticeCount = 0;

		uint32* mIndices = nullptr;
		uint32 mIndiceCount = 0;

		uint32 mMeshFlags = 0;

		uint64 mMeshID = 0;
	};
}