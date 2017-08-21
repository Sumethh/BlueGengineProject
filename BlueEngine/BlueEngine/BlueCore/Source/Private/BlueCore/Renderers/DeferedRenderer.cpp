#include "BlueCore/Renderers/DeferedRenderer.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include "BlueCore/Core/ApplicationWindow.h"
namespace Blue
{

	DeferedRenderer::DeferedRenderer()
	{

	}

	DeferedRenderer::~DeferedRenderer()
	{

	}

	void DeferedRenderer::Init()
	{
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();
		mFramebufferID = device->CreateGraphicsResource(EGraphicsResourceType::FrameBuffer);

		mPositionTextureID = device->CreateGraphicsResource(EGraphicsResourceType::Texture2D);
		mColorSpecTextureID = device->CreateGraphicsResource(EGraphicsResourceType::Texture2D);
		mNormalTextureID = device->CreateGraphicsResource(EGraphicsResourceType::Texture2D);

		device->BindGraphicsResource(mFramebufferID);
		ApplicationWindow* currentWindow = ApplicationWindow::GetCurrentWindow();
		mDepthBufferID = device->CreateGraphicsResource(EGraphicsResourceType::RenderBuffer);

		device->UpdateResourceData(mDepthBufferID, ERenderBufferType::DepthComponent, EBufferAttachment::DepthAttachmemt, currentWindow->GetWindowWidth(), currentWindow->GetWindowHeight());

		device->UpdateResourceData(mPositionTextureID, nullptr, currentWindow->GetWindowWidth(), currentWindow->GetWindowHeight(), EPrecisionType::RGB_F_16Bit, EImageFormat::RGB, EDataType::Float, 0);
		device->UpdateResourceData(mPositionTextureID, ETextureParameter::MinFilter, ETextureParameter::Nearest);
		device->UpdateResourceData(mPositionTextureID, ETextureParameter::MagFilter, ETextureParameter::Nearest);
		device->UpdateResourceData(mPositionTextureID, EBufferAttachment::ColorAttachment0);

		device->UpdateResourceData(mNormalTextureID, nullptr, currentWindow->GetWindowWidth(), currentWindow->GetWindowHeight(), EPrecisionType::RGB_F_16Bit, EImageFormat::RGB, EDataType::Float, 0);
		device->UpdateResourceData(mNormalTextureID, ETextureParameter::MinFilter, ETextureParameter::Nearest);
		device->UpdateResourceData(mNormalTextureID, ETextureParameter::MagFilter, ETextureParameter::Nearest);
		device->UpdateResourceData(mNormalTextureID, EBufferAttachment::ColorAttachment1);

		device->UpdateResourceData(mColorSpecTextureID, nullptr, currentWindow->GetWindowWidth(), currentWindow->GetWindowHeight(), EPrecisionType::RGBA_8Bit, EImageFormat::RGB, EDataType::UnsignedByte, 0);
		device->UpdateResourceData(mColorSpecTextureID, ETextureParameter::MinFilter, ETextureParameter::Nearest);
		device->UpdateResourceData(mColorSpecTextureID, ETextureParameter::MagFilter, ETextureParameter::Nearest);
		device->UpdateResourceData(mColorSpecTextureID, EBufferAttachment::ColorAttachment2);

		EBufferAttachment attachments[] = { EBufferAttachment::ColorAttachment0, EBufferAttachment::ColorAttachment1, EBufferAttachment::ColorAttachment2 };
		device->UpdateResourceData(mFramebufferID, attachments, 3);

		device->BindGraphicsResource(0);
	}

	void DeferedRenderer::SubmitGeometry(Mesh* aMesh, glm::mat4 aTransform)
	{

	}

	void DeferedRenderer::SetActiveCamera(CameraComponent* aCamera)
	{

	}

	void DeferedRenderer::SetActiveMaterial(Material* aMaterial)
	{

	}
}