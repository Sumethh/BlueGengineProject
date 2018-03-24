#include "BlueCore/Renderers/ForwardRenderer.h"
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/Vertex.h"
#include "BlueCore/Graphics/Mesh.h"
#include "BlueCore/Graphics/Material.h"
#include "BlueCore/Graphics/Shader.h"
#include "BlueCore/Graphics/Light.h"
#include "BlueCore/Managers/MeshManager.h"
#include "BlueCore/Managers/MaterialManager.h"
#include "BlueCore/Core/Transformable.h"
#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Managers/DebugManager.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.inl>
#include <GL/glew.h>


namespace Blue
{
	ForwardRenderer::ForwardRenderer() : mActiveViewMatrix(),
		mActiveProjectionMatrix(),
		mModelLocation(0),
		mActiveMaterial(nullptr)
	{
	}

	ForwardRenderer::~ForwardRenderer()
	{

	}

	void ForwardRenderer::SubmitGeometry(CapturedPrimitiveData& aPrimitiveData)
	{
		mCurrentShader->SetShaderVar(mModelLocation, (void*)&aPrimitiveData.modelMatrix, EVarType::Matrix4x4);

		IGraphicsDevice::GetCurrentGraphicsDevice()->DrawBuffersElements(EDrawMode::Triangles, mCurrentMesh->GetIndiceCount());
	}

	void ForwardRenderer::SetActiveCamera(CapturedCameraData& aCamera)
	{
		mActiveViewMatrix = glm::inverse(aCamera.viewMatrix);
		mActiveProjectionMatrix = aCamera.projectionMatrix;
	}

	void ForwardRenderer::SetActiveLighting(SceneLighting* aLighting)
	{
		(void)aLighting;
	}

	void ForwardRenderer::SetActiveMaterial(Material* aMaterial)
	{
		if (mActiveMaterial != aMaterial)
		{
			BlueAssert(aMaterial);
			mActiveMaterial = aMaterial;
			mActiveMaterial->Bind();
			mActiveMaterial->SetDataForDrawing();

			mCurrentShader = mActiveMaterial->GetShader();

			uint32 projectionLoc = mCurrentShader->GetShaderVariableLocation("projection");
			uint32 viewLoc = mCurrentShader->GetShaderVariableLocation("view");
			mModelLocation = mCurrentShader->GetShaderVariableLocation("model");
			mCurrentShader->SetShaderVar(projectionLoc, &mActiveProjectionMatrix, EVarType::Matrix4x4);
			mCurrentShader->SetShaderVar(viewLoc, &mActiveViewMatrix, EVarType::Matrix4x4);
		}
	}

	void ForwardRenderer::End()
	{
		mActiveProjectionMatrix = glm::mat4();
		mActiveViewMatrix = glm::mat4();
		mModelLocation = 0;
		mActiveMaterial->UnBind();
		mActiveMaterial = nullptr;
		if (mCurrentMesh)
		{
			mCurrentMesh->Unbind();
		}
		mCurrentMesh = nullptr;
	}
}