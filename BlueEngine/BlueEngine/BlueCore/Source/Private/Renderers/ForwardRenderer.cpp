#include "Renderers/ForwardRenderer.h"
#include "Core/Types.h"
#include "Core/Vertex.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Shader.h"
#include "Graphics/Light.h"
#include "Managers/MeshManager.h"
#include "Managers/MaterialManager.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Managers/DebugManager.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.inl>
#include <GL/glew.h>
namespace BlueCore
{

	ForwardRenderer::ForwardRenderer()
	{
		BoolDebugOptionType* debugOption = new BoolDebugOptionType();
		debugOption->debugName = "Draw Wireframe";
		debugOption->value = false;
		mWireframeDebugID = DebugManager::GI()->RegisterDebugOption(debugOption);
	}

	void ForwardRenderer::SubmitMesh(Mesh* aMesh, Material* aMaterial, Transform aTransform)
	{
		uint32 materialID = aMaterial->GetID();

		mRenderQueue[materialID][aMesh].push_back(aTransform);
	}

	void ForwardRenderer::SubmitCamera(CameraComponent* aCamera)
	{
		mCams.push_back(aCamera);
	}

	void ForwardRenderer::Flush()
	{
		BoolDebugOptionType* wireframe = (BoolDebugOptionType*)DebugManager::GI()->GetDebugOption(mWireframeDebugID);

		if (wireframe->value)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		MaterialManager* matManager = MaterialManager::GI();

		std::vector<Light*> lights;
		lights.reserve(32);
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();

		for (sizeInt i = 0; i < mCams.size(); ++i)
		{
			glm::mat4 projectionMatrix = mCams[i]->GetProjectionMatrix();
			glm::mat4 viewmatrix = mCams[i]->GetViewMatrix();

			for (auto matInfo : mRenderQueue)
			{
				const uint32 mat = matInfo.first;
				std::map < Mesh*, std::vector<Transform>>& renderList = matInfo.second;
				Material* material = matManager->GetMaterial(mat);
				material->Bind();
				material->SetDataForDrawing();
				Shader* shader = material->GetShader();
				int32 proj = shader->GetShaderVariableLocation("projection");
				int32 view = shader->GetShaderVariableLocation("view");
				shader->SetShaderVar(proj, glm::value_ptr(projectionMatrix), EVarType::Matrix4x4);
				shader->SetShaderVar(view, glm::value_ptr(viewmatrix), EVarType::Matrix4x4);
				int32 loc = shader->GetShaderVariableLocation("dl.color");
				glm::vec3 c(1.0);
				glm::vec3 dr(0, -1.0, 0);

				shader->SetShaderVar(loc , (void*)&c, EVarType::Vector3);
				loc = shader->GetShaderVariableLocation("dl.direction");
				shader->SetShaderVar(loc, (void*)&dr, EVarType::Vector3);


				for (auto& meshInfo : renderList)
				{
					Mesh* mesh = meshInfo.first;
					std::vector<Transform>& transforms = meshInfo.second;
					mesh->PrepForDrawing();
					uint32 indicieCount = mesh->GetIndiceCount();

					for (auto& transform : transforms)
					{
						glm::mat4 modelMat;
						modelMat = glm::translate(modelMat, transform.position);
						modelMat = glm::scale(modelMat, transform.scale);
						glm::quat q(transform.rotation);
						//modelMat *= glm::mat4_cast(q);
						int32 modelLoc = shader->GetShaderVariableLocation("model");

						material->SetPointLightData(lights);
						modelMat = transform.MakeMat4();
						shader->SetShaderVar(modelLoc, (void*)glm::value_ptr(modelMat), EVarType::Matrix4x4);

						device->DrawBuffersElements(EDrawMode::Triangles, indicieCount);
					}

					mesh->UnPrepForDrawing();
				}

				material->UnBind();
			}

		}

		mRenderQueue.clear();
		mCams.clear();

		if (wireframe->value)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

}