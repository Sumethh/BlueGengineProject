#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Types.h"
#include "Vertex.h"
#include "Defines.h"
namespace BlueGengine
{
	class VertexBuffer;
	class ElementBuffer;
	class VertexArray;

	class Mesh
	{
		private:
		enum MeshFlags
		{
			EReUploadVertices = BlueBit(0),
			ERebuildVerticesResource = BlueBit(1),
			EReUploadIndices = BlueBit(2),
			ERebuildIndicesResource = BlueBit(3)
		};
		public:


		Mesh(uint64 aId);
		//Mesh(Vertex* aVertexArray, uint32 aVertexCount, uint32* aIndices, uint32 aIndicieCount);
		~Mesh();

		void Init(Vertex* aVertexArray, uint32 aVertexCount, uint32* aIndices, uint32 aIndiceCount);

		inline Vertex* GetVertices() const { return mVertices; }
		inline uint32 GetVerticeCount() const { return mVerticeCount; }

		inline uint32 GetIndiceCount()const { return mIndiceCount; }
		inline uint32* GetIndices() const { return mIndices; }
		void SetVertices(Vertex* aVertices, uint32 aVerticeCount, bool aCleanUpOldVertecies = false);
		void SetIndices(uint32* aIndices, uint32 aIndiceCount, bool aCleanUpOldIndicies = false);

		inline void MarkVerticesForReUpload() { mMeshFlags |= MeshFlags::EReUploadVertices; }
		inline void MarkIndicesForReUpload() { mMeshFlags |= MeshFlags::EReUploadIndices; }

		inline void MarkVerticesForReBuild() { mMeshFlags |= MeshFlags::ERebuildVerticesResource; }
		inline void MarkIndicesForReBuild() { mMeshFlags |= MeshFlags::ERebuildIndicesResource; }

		inline bool NeedToReuploadIndices()const {return (mMeshFlags & MeshFlags::EReUploadIndices) > 0;}
		inline bool NeedToRebuildIndices()const { return (mMeshFlags & MeshFlags::ERebuildIndicesResource) > 0; }

		inline bool NeedToReuploadVertices()const { return (mMeshFlags & MeshFlags::EReUploadVertices) > 0; }
		inline bool NeedToRebuildVertices()const { return (mMeshFlags & MeshFlags::ERebuildVerticesResource) > 0; }

		inline bool NeedToUpdateGpuResource() const { return mMeshFlags > 0; }

		void UpdateMeshResources();

		void PrepForDrawing();
		void UnPrepForDrawing();

		uint64 GetID() const { return mMeshID; }

		private:

		inline void ResetFlag(MeshFlags aFlag) { mMeshFlags &= ~aFlag; }

		void ReUploadMeshInfo();
		void RebuildGpuResources();

		void InitBuffers();

		VertexBuffer* mVertexBuffer;
		ElementBuffer* mElementBuffer;
		VertexArray* mVertexArray;

		Vertex* mVertices;
		uint32 mVerticeCount;

		uint32* mIndices;
		uint32 mIndiceCount;

		uint32 mMeshFlags;

		uint64 mMeshID;
	};

}