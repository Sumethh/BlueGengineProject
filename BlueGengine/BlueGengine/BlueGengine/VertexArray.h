#pragma once

#include "Types.h"

namespace BlueGengine
{
	class VertexArrayImpl;
	class VertexArray
	{
		public:

		VertexArray();
		~VertexArray();

		void Build();
		void Bind();
		void UnBind();
		void Unload();
		private:
		VertexArrayImpl* m_impl;
	};
}