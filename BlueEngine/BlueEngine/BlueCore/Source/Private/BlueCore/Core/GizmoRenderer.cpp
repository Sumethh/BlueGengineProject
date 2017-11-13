#include "BlueCore/Renderers/GizmoRenderer.h"
#include "BlueCore/Managers/MeshManager.h"
#include "BlueCore/Managers/MaterialManager.h"
#include "BlueCore/Graphics/Material.h"
#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Core/Transformable.h"
#include "BlueCore/Graphics/Mesh.h"
#include "BlueCore/Graphics/Shader.h"
#include "BlueCore/GraphicsDevice/DataDescriptor.h"
#include "BlueCore/Managers/ShaderManager.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.inl>

namespace Blue
{
	glm::mat4 view;
	glm::mat4 proj;
	void GizmoRenderer::CreateLineRenderGraphicsResources(MappedRenderBufferInfo& aInfo)
	{
		static const uint32 lineDescriptorCount = 2;
		static DataDescriptor lineDescriptors[lineDescriptorCount] =
		{
			{ 0, 3, sizeof(glm::vec4) + sizeof(glm::vec3), 0, false, false, 0 },
			{ 1, 4, sizeof(glm::vec4) + sizeof(glm::vec3), sizeof(glm::vec3), false, false, 0 },
		};

		IGraphicsDevice* gd = IGraphicsDevice::GetCurrentGraphicsDevice();
		aInfo.vaoID = gd->CreateGraphicsResource(EGraphicsResourceType::VertexArrayBuffer);
		aInfo.vertexBufferID = gd->CreateGraphicsResource(EGraphicsResourceType::VertexBuffer);

		gd->BindGraphicsResource(aInfo.vaoID);
		gd->UpdateResourceData(aInfo.vertexBufferID, 0, nullptr, (sizeof(glm::vec4) + sizeof(glm::vec3)) * MAX_LINE_COUNT, lineDescriptors, lineDescriptorCount);
		gd->UnbindGraphicsResource(aInfo.vaoID);
	}

	GizmoRenderer::GizmoRenderer()
	{
		mCubeMesh = MeshManager::GI()->GetMeshAsync("cube", std::bind(&GizmoRenderer::SetCubeMesh, this, std::placeholders::_1));
		mSphereMesh = MeshManager::GI()->GetMeshAsync("sphere", std::bind(&GizmoRenderer::SetSphereMesh, this, std::placeholders::_1));
		mPlaneMesh = MeshManager::GI()->GetMeshAsync("plane", std::bind(&GizmoRenderer::SetPlaneMesh, this, std::placeholders::_1));
		mCapsuleMesh = MeshManager::GI()->GetMeshAsync("capsule", std::bind(&GizmoRenderer::SetCapsuleMesh, this, std::placeholders::_1));

		mDebugMaterial = MaterialManager::GI()->GetMaterial(MaterialManager::EDefaultMaterial::Debug);
		mDebugMaterialInstanced = MaterialManager::GI()->GetMaterial(MaterialManager::EDefaultMaterial::DebugInstanced);
		mGizmoMeshShader = ShaderManager::GI()->GetShader("GizmoMeshShader");

		mColorUniformLoc = mDebugMaterial->GetShaderVariableLoc("objectColor");
		mModelLoc = mDebugMaterial->GetShaderVariableLoc("model");
		mViewLoc = mDebugMaterial->GetShaderVariableLoc("view");
		mProjectionLoc = mDebugMaterial->GetShaderVariableLoc("projection");

		MappedRenderBufferInfo info;
		info.lineCount = 0;
		CreateLineRenderGraphicsResources(info);
		mLineRenderinfo.push_back(info);
	}

	GizmoRenderer::~GizmoRenderer()
	{

	}

	void GizmoRenderer::DrawMesh(Mesh* aMesh, glm::vec3 aColor)
	{
		mGizmoMeshShader->Bind();
		uint32 colorLoc = mGizmoMeshShader->GetShaderVariableLocation("objectColor");
		uint32 projLoc = mGizmoMeshShader->GetShaderVariableLocation("projection");
		uint32 viewLoc = mGizmoMeshShader->GetShaderVariableLocation("view");
		mGizmoMeshShader->SetShaderVar(colorLoc, (void*)glm::value_ptr(glm::vec4(aColor, mAlpha)), EVarType::Vector4);
		mGizmoMeshShader->SetShaderVar(projLoc, (void*)glm::value_ptr(proj), EVarType::Matrix4x4);
		mGizmoMeshShader->SetShaderVar(viewLoc, (void*)glm::value_ptr(view), EVarType::Matrix4x4);

		aMesh->PrepForDrawing();
		IGraphicsDevice::GetCurrentGraphicsDevice()->DrawBuffersElements(EDrawMode::Triangles, aMesh->GetIndiceCount());
		aMesh->UnPrepForDrawing();
		mDebugMaterial->Bind();
	}

	void GizmoRenderer::DrawSphere(glm::vec3 aPosition, glm::vec3 aScale, glm::vec3 aColor, EGizmoMode aMode)
	{
		Transform trans;
		trans.position = aPosition;
		trans.scale = aScale;
		trans.rotation = glm::quat();
		glm::mat4 modelMat = trans.MakeMat4();
		Shader* shader = mDebugMaterial->GetShader();
		glm::vec4 col(aColor, mAlpha);
		shader->SetShaderVar(mColorUniformLoc, glm::value_ptr(col), EVarType::Vector4);
		shader->SetShaderVar(mModelLoc, glm::value_ptr(modelMat), EVarType::Matrix4x4);
		mSphereMesh->PrepForDrawing();
		IGraphicsDevice::GetCurrentGraphicsDevice()->DrawBuffersElements(EDrawMode::Triangles, mSphereMesh->GetIndiceCount());
		mSphereMesh->UnPrepForDrawing();
	}

	void GizmoRenderer::DrawCube(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 aColor, EGizmoMode aMode)
	{
		Transform trans;
		trans.position = aPosition;
		trans.scale = aScale;
		trans.rotation = aRotation;
		glm::mat4 modelMat = trans.MakeMat4();
		Shader* shader = mDebugMaterial->GetShader();
		glm::vec4 color(aColor, mAlpha);
		shader->SetShaderVar(mColorUniformLoc, glm::value_ptr(color), EVarType::Vector4);
		shader->SetShaderVar(mModelLoc, glm::value_ptr(modelMat), EVarType::Matrix4x4);
		mCubeMesh->PrepForDrawing();
		IGraphicsDevice::GetCurrentGraphicsDevice()->DrawBuffersElements(EDrawMode::Triangles, mCubeMesh->GetIndiceCount());
		mCubeMesh->UnPrepForDrawing();
	}

	struct LineData
	{
		glm::vec3 Pos1;
		glm::vec4 Color1;
		glm::vec3 Pos2;
		glm::vec4 Color2;
	};


	void GizmoRenderer::DrawLine(glm::vec3 aStart, glm::vec3 aEnd, glm::vec3 color)
	{
		LineData data = {};
		data.Pos1 = aStart;
		data.Pos2 = aEnd;
		glm::vec4 col(color.x, color.y, color.z, 1.0f);
		data.Color1 = data.Color2 = col;
		IGraphicsDevice* gd = IGraphicsDevice::GetCurrentGraphicsDevice();
		bool lineAdded = false;

		for (int i = 0; i < mLineRenderinfo.size(); ++i)
		{
			MappedRenderBufferInfo& info = mLineRenderinfo[i];

			if (info.lineCount < MAX_LINE_COUNT)
			{
				gd->UpdateResourceData(info.vertexBufferID, info.lineCount * sizeof(LineData), &data, sizeof(LineData));
				info.lineCount++;
				lineAdded = true;
			}
		}

		if (!lineAdded)
		{
			MappedRenderBufferInfo info = {};
			CreateLineRenderGraphicsResources(info);
			gd->UpdateResourceData(info.vertexBufferID, info.lineCount * sizeof(LineData), &data, sizeof(LineData));
			info.lineCount++;
			mLineRenderinfo.push_back(info);
		}
	}

	void GizmoRenderer::DrawPlane(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 aColor, EGizmoMode aMode)
	{
		Transform trans;
		trans.position = aPosition;
		trans.scale = aScale;
		trans.rotation = aRotation;
		glm::mat4 modelMat = trans.MakeMat4();
		Shader* shader = mDebugMaterial->GetShader();
		glm::vec4 col(aColor, mAlpha);
		shader->SetShaderVar(mColorUniformLoc, glm::value_ptr(col), EVarType::Vector4);
		shader->SetShaderVar(mModelLoc, glm::value_ptr(modelMat), EVarType::Matrix4x4);
		mPlaneMesh->PrepForDrawing();
		IGraphicsDevice::GetCurrentGraphicsDevice()->DrawBuffersElements(EDrawMode::Triangles, mPlaneMesh->GetIndiceCount());
		mPlaneMesh->UnPrepForDrawing();
	}

	void GizmoRenderer::DrawCapsule(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 aColor, EGizmoMode aMode)
	{
		Transform trans;
		trans.position = aPosition;
		trans.scale = aScale;
		trans.rotation = aRotation;
		glm::mat4 modelMat = trans.MakeMat4();
		Shader* shader = mDebugMaterial->GetShader();
		glm::vec4 col(aColor, mAlpha);
		shader->SetShaderVar(mColorUniformLoc, glm::value_ptr(col), EVarType::Vector4);
		shader->SetShaderVar(mModelLoc, glm::value_ptr(modelMat), EVarType::Matrix4x4);
		mCapsuleMesh->PrepForDrawing();
		IGraphicsDevice::GetCurrentGraphicsDevice()->DrawBuffersElements(EDrawMode::Triangles, mCapsuleMesh->GetIndiceCount());
		mCapsuleMesh->UnPrepForDrawing();
	}


	void GizmoRenderer::Begin(CameraComponent* aActiveCamera)
	{
		mDebugMaterial->Bind();
		view = glm::inverse(aActiveCamera->GetViewMatrix());
		proj = aActiveCamera->GetProjectionMatrix();
		Shader* shader = mDebugMaterial->GetShader();
		shader->SetShaderVar(mViewLoc, (void*)glm::value_ptr(view), EVarType::Matrix4x4);
		shader->SetShaderVar(mProjectionLoc, (void*)glm::value_ptr(proj), EVarType::Matrix4x4);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void GizmoRenderer::Flush()
	{
		glDisable(GL_BLEND);
		RenderLines();
		glDepthFunc(GL_LESS);
	}


	void GizmoRenderer::RenderLines()
	{
		IGraphicsDevice* gd = IGraphicsDevice::GetCurrentGraphicsDevice();
		mDebugMaterialInstanced->Bind();
		Shader* shader = ShaderManager::GI()->GetShader("GizmoLineShader");
		uint32 viewLoc = shader->GetShaderVariableLocation("view");
		uint32 projLoc = shader->GetShaderVariableLocation("projection");
		shader->SetShaderVar(viewLoc, (void*)glm::value_ptr(view), EVarType::Matrix4x4);
		shader->SetShaderVar(projLoc, (void*)glm::value_ptr(proj), EVarType::Matrix4x4);

		for (int i = 0; i < mLineRenderinfo.size(); ++i)
		{
			MappedRenderBufferInfo& info = mLineRenderinfo[i];

			if (!info.lineCount)
			{
				continue;
			}

			gd->BindGraphicsResource(info.vaoID);

			gd->DrawBuffers(EDrawMode::Lines, 0, info.lineCount * 2);

			gd->UnbindGraphicsResource(info.vaoID);

			info.lineCount = 0;
		}

		mDebugMaterialInstanced->UnBind();
	}
}