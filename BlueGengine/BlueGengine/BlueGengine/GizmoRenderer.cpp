#include "GizmoRenderer.h"
#include "MeshManager.h"
#include "MaterialManager.h"
#include "Material.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Mesh.h"
#include "Shader.h"
#include "DataDescriptor.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.inl>

namespace BlueGengine
{

	void GizmoRenderer::CreateLineRenderGraphicsResources(LineRenderInfo& aInfo)
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
		gd->UnBindGraphicsResource(aInfo.vaoID);

	}

	GizmoRenderer::GizmoRenderer()
	{
		mCubeMesh = MeshManager::GI()->GetMeshAsync("cube", std::bind(&GizmoRenderer::SetCubeMesh, this, std::placeholders::_1));
		mDebugMaterial = MaterialManager::GI()->GetMaterial(MaterialManager::EDefaultMaterial::Debug);
		mDebugMaterialInstanced = MaterialManager::GI()->GetMaterial(MaterialManager::EDefaultMaterial::DebugInstanced);

		mColorUniformLoc = mDebugMaterial->GetShaderVariableLoc("objectColor");
		mModelLoc = mDebugMaterial->GetShaderVariableLoc("model");
		mViewLoc = mDebugMaterial->GetShaderVariableLoc("view");
		mProjectionLoc = mDebugMaterial->GetShaderVariableLoc("projection");

		LineRenderInfo info;
		info.lineCount = 0;
		CreateLineRenderGraphicsResources(info);
		mLineRenderinfo.push_back(info);
	}

	GizmoRenderer::~GizmoRenderer()
	{

	}

	void GizmoRenderer::DrawSphere(glm::vec3 aPosition, glm::vec3 aScale, glm::vec3 aColor, EGizmoMode aMode)
	{

	}

	void GizmoRenderer::DrawCube(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 aColor, EGizmoMode aMode)
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
		glm::vec4 col(color.x , color.y, color.z, 1.0f);
		data.Color1 = data.Color2 = col;
		IGraphicsDevice* gd = IGraphicsDevice::GetCurrentGraphicsDevice();
		LineRenderInfo& info = mLineRenderinfo[0];
		gd->UpdateResourceData(info.vertexBufferID, info.lineCount * sizeof(LineData), &data, sizeof(LineData));
		info.lineCount++;
	}

	void GizmoRenderer::DrawPlane(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 aColor, EGizmoMode aMode)
	{

	}

	void GizmoRenderer::DrawCapsule(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 color, EGizmoMode aMode)
	{

	}
	glm::mat4 view;
	glm::mat4 proj;
	void GizmoRenderer::Begin(CameraComponent* aActiveCamera)
	{
		mDebugMaterial->Bind();
		view	= aActiveCamera->GetViewMatrix();
		proj	= aActiveCamera->GetProjectionMatrix();
		Shader* shader = mDebugMaterial->GetShader();
		shader->SetShaderVar(mViewLoc, (void*) glm::value_ptr(view), EVarType::Matrix4x4);
		shader->SetShaderVar(mProjectionLoc, (void*) glm::value_ptr(proj), EVarType::Matrix4x4);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void GizmoRenderer::Flush()
	{
		glDisable(GL_BLEND);
		glLineWidth(3.0f);
		IGraphicsDevice* gd = IGraphicsDevice::GetCurrentGraphicsDevice();
		LineRenderInfo& info = mLineRenderinfo[0];
		mDebugMaterialInstanced->Bind();
		Shader* shader = mDebugMaterialInstanced->GetShader();
		uint32 viewLoc = shader->GetShaderVariableLocation("view");
		uint32 projLoc = shader->GetShaderVariableLocation("projection");

		shader->SetShaderVar(viewLoc, (void*)glm::value_ptr(view), EVarType::Matrix4x4);
		shader->SetShaderVar(projLoc, (void*)glm::value_ptr(proj), EVarType::Matrix4x4);
		gd->BindGraphicsResource(info.vaoID);
		gd->DrawBuffers(EDrawMode::Lines, 0, info.lineCount * 2);
		gd->UnBindGraphicsResource(info.vaoID);
		info.lineCount = 0;
		mDebugMaterialInstanced->UnBind();

	}

}