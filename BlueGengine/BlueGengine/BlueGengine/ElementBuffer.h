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
		void SetData(uint32* aData, uint32 aDataSize);
		void Bind();
		void UnBind();

		private:
		ElementBufferImpl* mImpl;

	};
}
