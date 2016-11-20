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


		void SetData(void* aData, uint32 aDataSize, DataDescriptor* aDescriptors, uint32 aDescriptorCount, bool aMapBuffer = false);
		void BeginMap();
		void MapData(void* aData, uint32 aDataSize);

		//This assumes that the data that is being received follows the same rules as specified when SetData was called
		void ReUploadData(void* aData, uint32 aDataSize);
		void Unload();
		void EndMap();
		void Bind();
		void UnBind();
		private:
		VertexBufferImpl* mImpl;
	};
}
