#pragma once
#include "../Types.h"
namespace BlueGengine
{
	struct DataDescriptor;
	class VertexBufferImpl
	{
		public:
		VertexBufferImpl() {};
		virtual ~VertexBufferImpl() {};
		virtual void SetData(void* a_data, uint32 a_dataSize, DataDescriptor* a_descriptors, uint32 a_descriptorCount, bool a_mapBuffer = false) = 0;

		virtual void ReUploadData(void* a_data, uint32 a_dataSize) = 0;
		virtual void Rebuild() = 0;


		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void Unload() = 0;
	};

	class OpenlGlVertexBufferImpl : public VertexBufferImpl
	{
		public:
		OpenlGlVertexBufferImpl();
		~OpenlGlVertexBufferImpl();
		virtual void SetData(void* a_data, uint32 a_dataSize, DataDescriptor* a_descriptors, uint32 a_descriptorCount, bool a_mapBuffer = false) override;
		void ReUploadData(void* a_data, uint32 a_dataSize) override;
		virtual void Rebuild() override;
		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void Unload() override;
		private:
		uint32 m_vbo;
	};
}
