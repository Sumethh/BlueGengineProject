#include "ForwardRenderer.h"
#include "../Types.h"
#include "../Mesh.h"
#include "../Material.h"
#include "../MeshManager.h"
#include "../MaterialManager.h"
#include "../Vertex.h"
#include "../shader.h"
#include "../Light.h"
#include "../Components/TransformComponent.h"
#include "../Components/CameraComponent.h"
#include <glm/gtc/quaternion.hpp>
#include <gl/glew.h>
#include <glm/gtc/type_ptr.inl>
namespace BlueGengine
{

	ForwardRenderer::ForwardRenderer()
	{
		for (int i = 0; i < 32; i++)
		{
			Light* l = new Light();
			l->position.x = i * 3;
			l->position.y = 0;
			l->position.z = 0;

			l->color.x = 1.0f;
			l->color.y = 0;
			l->color.z = 0;
			Tlights.push_back(l);
		}

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
		MaterialManager* matManager = MaterialManager::GI();
		MeshManager* meshManager = MeshManager::GI();
		std::vector<Light*> lights;
		lights.reserve(32);

		//lights.push_back(myLight);
		for (int i = 0; i < 32; i++)
		{
			lights.push_back(Tlights[i]);
		}

		for (int i = 0; i < mCams.size(); ++i)
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
				Shader* shader = material->m_shader;
				int32 proj = glGetUniformLocation(shader->GetShaderID(), "projection");
				int32 view = glGetUniformLocation(shader->GetShaderID(), "view");
				glUniformMatrix4fv(proj, 1, false, glm::value_ptr(projectionMatrix));
				glUniformMatrix4fv(view, 1, false, glm::value_ptr(viewmatrix));
				int32 loc = glGetUniformLocation(shader->GetShaderID(), "dl.color");
				glUniform3f(loc, 1.0, 1.0f, 1.0f);
				loc = glGetUniformLocation(shader->GetShaderID(), "dl.direction");
				glUniform3f(loc, 0.0f, -1.0f, 0.0f);

				for (auto& meshInfo : renderList)
				{
					Mesh* mesh = meshInfo.first;
					std::vector<Transform>& transforms = meshInfo.second;
					mesh->PrepForDrawing();

					for (auto& transform : transforms)
					{
						glm::mat4 modelMat;
						modelMat = glm::translate(modelMat, transform.position);
						modelMat = glm::scale(modelMat, transform.scale);
						glm::quat q(transform.rotation);
						//modelMat *= glm::mat4_cast(q);
						int32 modelLoc = glGetUniformLocation(shader->GetShaderID(), "model");

						material->SetPointLightData(lights);
						modelMat = transform.MakeMat4();
						glUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(modelMat));

						glDrawElements(GL_TRIANGLES, mesh->GetIndiceCount(), GL_UNSIGNED_INT, nullptr);

					}

					mesh->UnPrepForDrawing();
				}

				material->Unprep();
			}

		}

		mRenderQueue.clear();
		mCams.clear();
	}

}