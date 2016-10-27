#pragma once
#include "Types.h"
namespace BlueGengine
{
	class ElementBufferImpl;
	class ElementBuffer
	{
		public:
		ElementBuffer();
		~ElementBuffer();

		void Build();
		void Unload();
		void SetData(uint32* a_data, uint32 a_dataSize);
		void Bind();
		void UnBind();

		private:
		ElementBufferImpl* m_impl;

	};
}
