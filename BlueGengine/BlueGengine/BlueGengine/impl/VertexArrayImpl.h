#pragma once
#include "../Types.h"
namespace BlueGengine
{
	class VertexArrayImpl
	{
		public:
		VertexArrayImpl() {};
		virtual ~VertexArrayImpl() {};
		virtual void Build() = 0;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void Unload() = 0;
	};

	class OpenGLVertexArrayImpl : public VertexArrayImpl
	{
		public:
		OpenGLVertexArrayImpl();
		~OpenGLVertexArrayImpl();
		virtual void Build() override;
		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void Unload() override;
		private:
		uint32 m_vao;
	};
}
