#include "BlueCore/Graphics/GraphicsResource.h"
#include "BlueCore/Tasks/UpdateGraphicsResourceTask.h"

namespace Blue
{

	GraphicsResource::GraphicsResource() : mDirty(0)
	{

	}

	GraphicsResource::~GraphicsResource()
	{
		if (mGraphicsResource)
		{
			Destruct();
		}
	}

	void GraphicsResource::Destruct()
	{
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();
		device->DeleteGraphicsResource(mGraphicsResource);
	}

	void GraphicsResource::QueueResourceUpdate()
	{
		UpdateGraphicsResourceTask* updateResourceTask = new UpdateGraphicsResourceTask();
		updateResourceTask->graphicsResourceToUpdate = this;
		TaskSystem::SubmitTask(updateResourceTask);
	}

	void GraphicsResource::Bind()
	{
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();
		device->BindGraphicsResource(mGraphicsResource);
	}

	void GraphicsResource::Unbind()
	{
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();
		device->UnbindGraphicsResource(mGraphicsResource);
	}

	bool GraphicsResource::IsValid()
	{
		return mGraphicsResource > 0;
	}

	bool GraphicsResource::IsDirty()
	{
		return mDirty;
	}

	void GraphicsResource::MarkDirty()
	{
		mDirty = true;
	}

}