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
		virtual void SetData(void* aData, uint32 aDataSize, DataDescriptor* aDescriptors, uint32 aDescriptorCount, bool aMapBuffer = false) = 0;

		virtual void ReUploadData(void* aData, uint32 aDataSize) = 0;
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
		virtual void SetData(void* aData, uint32 aDataSize, DataDescriptor* aDescriptors, uint32 aDescriptorCount, bool aMapBuffer = false) override;
		void ReUploadData(void* aData, uint32 aDataSize) override;
		virtual void Rebuild() override;
		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void Unload() override;
		private:
		uint32 mVbo;
	};
}
