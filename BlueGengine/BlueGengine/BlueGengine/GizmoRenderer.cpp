#include "GizmoRenderer.h"
#include "MeshManager.h"
#include "MaterialManager.h"
#include "Material.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Mesh.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.inl>

namespace BlueGengine
{

	GizmoRenderer::GizmoRenderer()
	{
		mCubeMesh = MeshManager::GI()->GetMeshAsync("cube", std::bind(&GizmoRenderer::SetCubeMesh, this, std::placeholders::_1));
		mDebugMaterial = MaterialManager::GI()->GetMaterial(MaterialManager::EDefaultMaterial::Debug);

		mColorUniformLoc = mDebugMaterial->GetShaderVariableLoc("objectColor");
		mModelLoc = mDebugMaterial->GetShaderVariableLoc("model");
		mViewLoc = mDebugMaterial->GetShaderVariableLoc("view");
		mProjectionLoc = mDebugMaterial->GetShaderVariableLoc("projection");
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
		glUniform4f(mColorUniformLoc, aColor.x, aColor.y, aColor.z, mAlpha);
		glUniformMatrix4fv(mModelLoc, 1, false, glm::value_ptr(modelMat));
		mCubeMesh->PrepForDrawing();
		glDrawElements(GL_TRIANGLES, mCubeMesh->GetIndiceCount(), GL_UNSIGNED_INT, nullptr);

		mCubeMesh->UnPrepForDrawing();
	}

	void GizmoRenderer::DrawLine(glm::vec3 aStart, glm::vec3 aEnd, glm::vec3 color)
	{

	}

	void GizmoRenderer::DrawPlane(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 aColor, EGizmoMode aMode)
	{

	}

	void GizmoRenderer::DrawCapsule(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 color, EGizmoMode aMode)
	{

	}

	void GizmoRenderer::Begin(CameraComponent* aActiveCamera)
	{
		mDebugMaterial->Bind();
		glm::mat4 view = aActiveCamera->GetViewMatrix();
		glm::mat4 proj = aActiveCamera->GetProjectionMatrix();
		glUniformMatrix4fv(mViewLoc, 1, false, glm::value_ptr(view));
		glUniformMatrix4fv(mProjectionLoc, 1, false, glm::value_ptr(proj));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void GizmoRenderer::Flush()
	{
		glDisable(GL_BLEND);

	}

}