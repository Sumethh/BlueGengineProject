#pragma once

#include "BlueCore/Core/Types.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"


namespace Blue
{
	class GraphicsResource
	{
	public:
		GraphicsResource();
		virtual ~GraphicsResource();

		virtual void Create() = 0;
		virtual void Destruct();

		virtual void UpdateResource() = 0;
		void QueueResourceUpdate();
		virtual void Bind();
		virtual void Unbind();

		bool IsValid();

		bool IsDirty();
		void MarkDirty();

	protected:

		uint32 mGraphicsResource = 0;

	private:

		uint8 mDirty : 1;

	};
}
