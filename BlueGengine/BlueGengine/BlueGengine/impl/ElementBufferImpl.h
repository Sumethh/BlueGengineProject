#pragma once
#include "../Types.h"

namespace BlueGengine
{
	class ElementBufferImpl
	{
		public:
		virtual void Build() = 0;
		virtual void Unload() = 0;
		virtual void SetData(uint32* a_data, uint32 a_dataSize) = 0 ;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
	};

	class OpenlGlElementBufferImpl : public ElementBufferImpl
	{
		public:
		OpenlGlElementBufferImpl();
		~OpenlGlElementBufferImpl();
		virtual void Build();
		virtual void Unload() ;
		virtual void SetData(uint32* a_data, uint32 a_dataSize);
		virtual void Bind();
		virtual void UnBind();
		private:
		uint32 m_ebo;
	};
}
