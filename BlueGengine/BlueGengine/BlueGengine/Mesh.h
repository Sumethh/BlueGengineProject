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


		Mesh(uint32 a_id);
		//Mesh(Vertex* a_vertexArray, uint32 a_vertexCount, uint32* a_indices, uint32 a_indicieCount);
		~Mesh();

		void Init(Vertex* a_vertexArray, uint32 a_vertexCount, uint32* a_indices, uint32 a_indiceCount);

		inline Vertex* GetVertices() const { return m_vertices; }
		inline uint32 GetVerticeCount() const { return m_verticeCount; }

		inline uint32 GetIndiceCount()const { return m_indiceCount; }
		inline uint32* GetIndices() const { return m_indices; }
		void SetVertices(Vertex* a_vertices, uint32 a_verticeCount, bool a_cleanUpOldVertecies = false);
		void SetIndices(uint32* a_indices, uint32 a_indiceCount, bool a_cleanUpOldIndicies = false);

		inline void MarkVerticesForReUpload() { m_meshFlags |= MeshFlags::EReUploadVertices; }
		inline void MarkIndicesForReUpload() { m_meshFlags |= MeshFlags::EReUploadIndices; }

		inline void MarkVerticesForReBuild() { m_meshFlags |= MeshFlags::ERebuildVerticesResource; }
		inline void MarkIndicesForReBuild() { m_meshFlags |= MeshFlags::ERebuildIndicesResource; }

		inline bool NeedToReuploadIndices()const {return (m_meshFlags & MeshFlags::EReUploadIndices) > 0;}
		inline bool NeedToRebuildIndices()const { return (m_meshFlags & MeshFlags::ERebuildIndicesResource) > 0; }

		inline bool NeedToReuploadVertices()const { return (m_meshFlags & MeshFlags::EReUploadVertices) > 0; }
		inline bool NeedToRebuildVertices()const { return (m_meshFlags & MeshFlags::ERebuildVerticesResource) > 0; }

		inline bool NeedToUpdateGpuResource() const { return m_meshFlags > 0; }

		void UpdateMeshResources();

		void PrepForDrawing();
		void UnPrepForDrawing();

		uint32 GetID() const { return m_meshID; }

		private:

		inline void ResetFlag(MeshFlags a_flag) { m_meshFlags &= ~a_flag; }

		void ReUploadMeshInfo();
		void RebuildGpuResources();

		void InitBuffers();

		VertexBuffer* m_vertexBuffer;
		ElementBuffer* m_elementBuffer;
		VertexArray* m_vertexArray;

		Vertex* m_vertices;
		uint32 m_verticeCount;

		uint32* m_indices;
		uint32 m_indiceCount;

		uint32 m_meshFlags;

		uint32 m_meshID;
	};

}