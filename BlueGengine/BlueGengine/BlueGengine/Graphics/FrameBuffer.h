#pragma once

namespace BlueGengine
{
	class FrameBufferImpl;
	class FrameBuffer
	{
		public:
		FrameBuffer();
		~FrameBuffer();
		void Bind();
		void UnBind();
		void Clear() ;
		void Recreate() ;
		private:
		FrameBufferImpl* mImpl;
	};
}