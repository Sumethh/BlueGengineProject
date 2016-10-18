#pragma once
#include "NonCopyable.h"
#include "Types.h"
#include "DataDescriptor.h"
namespace BlueGengine
{
	class VertexBufferImpl;
	class VertexBuffer : NonCopyable
	{
		public:

		VertexBuffer();
		~VertexBuffer();


		void SetData(void* a_data, uint32 a_dataSize, DataDescriptor* a_descriptors, uint32 a_descriptorCount, bool a_mapBuffer = false);
		void BeginMap();
		void MapData(void* a_data, uint32 a_dataSize);

		//This assumes that the data that is being received follows the same rules as specified when SetData was called
		void ReUploadData(void* a_data, uint32 a_dataSize);
		void Unload();
		void EndMap();
		void Bind();
		void UnBind();
		private:
		VertexBufferImpl* m_impl;
	};
}
