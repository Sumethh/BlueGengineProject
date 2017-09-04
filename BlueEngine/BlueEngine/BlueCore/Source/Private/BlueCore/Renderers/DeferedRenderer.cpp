#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include "BlueCore/Renderers/DeferedRenderer.h"

#include "BlueCore/Graphics/Mesh.h"
#include "BlueCore/Graphics/Shader.h"
#include "BlueCore/Graphics/Material.h"

#include "BlueCore/Managers/DebugManager.h"

#include "BlueCore/Core/ApplicationWindow.h"
#include "BlueCore/Core/Rect.h"

#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Core/Transformable.h"
#include <gl/glew.h>
#include <Imgui/imgui.h>
namespace Blue
{
	DeferedRenderer::DeferedRenderer() : mDeferedShader(nullptr), mLightingPassShader(nullptr), mCurrentMaterial(nullptr), mModelLocation(0)
	{
	}

	DeferedRenderer::~DeferedRenderer()
	{

	}
	glm::vec3 color(.6, .6, .6);
	glm::vec3 direction(0, -1, 0);

	void DeferedRenderer::Init()
	{
		BEGIN_DEBUG_GROUP("Lighting");
		ADD_DEBUG_TWEAKABLE(color);
		ADD_DEBUG_TWEAKABLE(direction);
		END_DEBUG_GROUP();

		mDeferedShader = new Shader();
		mDeferedShader->LoadShader("Assets/Shaders/GLSL/Defered/GBuffer.glslv", "Assets/Shaders/GLSL/Defered/GBuffer.glslf");

		mLightingPassShader = new Shader();
		mLightingPassShader->LoadShader("Assets/Shaders/GlSL/Defered/LightPass.glslv", "Assets/Shaders/GlSL/Defered/LightPass.glslf");

		mModelLocation = mDeferedShader->GetShaderVariableLocation("model");
		mProjectionLocation = mDeferedShader->GetShaderVariableLocation("projection");
		mViewLocation = mDeferedShader->GetShaderVariableLocation("view");

		mLightPassViewPosition = mLightingPassShader->GetShaderVariableLocation("viewPos");
		mDirLightCountPosition = mLightingPassShader->GetShaderVariableLocation("directionalLightCount");
		mPointLightCountPosition = mLightingPassShader->GetShaderVariableLocation("pointLightCount");

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

		float quadVertices[] =
		{
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};

		mQuadVao = device->CreateGraphicsResource(EGraphicsResourceType::VertexArrayBuffer);
		mQuadVbo = device->CreateGraphicsResource(EGraphicsResourceType::VertexBuffer);
		device->BindGraphicsResource(mQuadVao);

		DataDescriptor vertexDescriptors[2] =
		{
			{0, 3, sizeof(float) * 5, 0, false, false, 0 },
			{1, 2, sizeof(float) * 5, sizeof(float) * 3, false, false}
		};
		device->UpdateResourceData(mQuadVbo, 0, static_cast<void*>(quadVertices), sizeof(quadVertices), vertexDescriptors, 2);
		device->UnbindGraphicsResource(mQuadVao);
	}
	void DeferedRenderer::Begin()
	{
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();
		device->BindGraphicsResource(mFramebufferID);
		device->ClearBuffer((EBufferBit)((uint8)EBufferBit::Color | (uint8)EBufferBit::DepthBit));
		mDeferedShader->Bind();

	}

	void DeferedRenderer::End()
	{
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();
		mCurrentMesh->UnPrepForDrawing();
		mCurrentMesh = nullptr;
		device->BindGraphicsResource(0);

		mLightingPassShader->Bind();
		Transformable* transformable = reinterpret_cast<Transformable*>(mCurrentCamera->GetOwner());
		Transform trans = transformable->GetTransform();

		int32 lightCount = 0;
		mLightingPassShader->SetShaderVar(mLightPassViewPosition, static_cast<void*>(&trans.position), EVarType::Vector3);
		mLightingPassShader->SetShaderVar(mPointLightCountPosition, &lightCount, EVarType::Int);
		mLightingPassShader->SetShaderVar(mDirLightCountPosition, &lightCount, EVarType::Int);

		glActiveTexture(GL_TEXTURE0);
		device->BindGraphicsResource(mPositionTextureID);
		glActiveTexture(GL_TEXTURE1);
		device->BindGraphicsResource(mNormalTextureID);
		glActiveTexture(GL_TEXTURE2);
		device->BindGraphicsResource(mColorSpecTextureID);

		int32 dirLightDirLoc = mLightingPassShader->GetShaderVariableLocation("directionalLights[0].direction");
		int32 dirLightColorLoc = mLightingPassShader->GetShaderVariableLocation("directionalLights[0].color");

		int32 count = 1;
		mLightingPassShader->SetShaderVar(dirLightDirLoc, static_cast<void*>(&direction), EVarType::Vector3);
		mLightingPassShader->SetShaderVar(dirLightColorLoc, static_cast<void*>(&color), EVarType::Vector3);

		mLightingPassShader->SetShaderVar(mDirLightCountPosition, &count, EVarType::Int);

		device->BindGraphicsResource(mQuadVao);
		device->DrawBuffers(EDrawMode::TriangleStrip, 0, 4);
		device->UnbindGraphicsResource(mQuadVao);

		mLightingPassShader->UnBind();

		IntRect rect;
		rect.topLeft = glm::ivec2(0, 0);
		rect.extents = glm::ivec2(ApplicationWindow::GetWindowWidth(), ApplicationWindow::GetWindowHeight());
		device->BlitFramebuffers(mFramebufferID, 0, rect, rect, EBufferBit::DepthBit);
		device->BindGraphicsResource(0);
	}

	void DeferedRenderer::SubmitGeometry(Mesh* aMesh, glm::mat4 aTransform)
	{
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();
		if (mCurrentMesh != aMesh)
		{
			aMesh->PrepForDrawing();
			mCurrentMesh = aMesh;
		}
		mDeferedShader->SetShaderVar(mModelLocation, &aTransform, EVarType::Matrix4x4);
		device->DrawBuffersElements(EDrawMode::Triangles, aMesh->GetIndiceCount());
	}

	void DeferedRenderer::SetActiveCamera(CameraComponent* aCamera)
	{
		mCurrentProjectionMatrix = aCamera->GetProjectionMatrix();
		mDeferedShader->SetShaderVar(mProjectionLocation, &mCurrentProjectionMatrix, EVarType::Matrix4x4);
		glm::mat4 view = glm::inverse(aCamera->GetViewMatrix());
		mDeferedShader->SetShaderVar(mViewLocation, static_cast<void*>(&view), EVarType::Matrix4x4);
		mCurrentCamera = aCamera;
	}

	void DeferedRenderer::SetActiveMaterial(Material* aMaterial)
	{
		aMaterial->Bind(false);
		aMaterial->SetDataForDrawing(mDeferedShader);
		mCurrentMaterial = aMaterial;
	}
}