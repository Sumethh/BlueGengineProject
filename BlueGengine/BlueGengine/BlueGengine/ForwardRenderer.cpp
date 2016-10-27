#include "ForwardRenderer.h"
#include "Types.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshManager.h"
#include "MaterialManager.h"
#include <gl/glew.h>
#include "Vertex.h"
#include "shader.h"
#include <glm/gtc/type_ptr.inl>
#include "Light.h"
#include <glm/gtc/quaternion.hpp>
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
namespace BlueGengine
{
	void ForwardRenderer::SubmitMesh(Mesh* a_mesh, Material* a_material, Transform a_transform)
	{
		uint32 meshID = a_mesh->GetID();
		uint32 materialID = a_material->GetID();

		m_renderQueue[materialID][meshID].push_back(a_transform);
	}

	void ForwardRenderer::SubmitCamera(CameraComponent* a_camera)
	{
		m_cams.push_back(a_camera);
	}

	void ForwardRenderer::Flush()
	{
		MaterialManager* matManager = MaterialManager::GI();
		MeshManager* meshManager = MeshManager::GI();

		for (int i = 0; i < m_cams.size(); ++i)
		{
			glm::mat4 projectionMatrix = m_cams[i]->GetProjectionMatrix();
			glm::mat4 viewmatrix = m_cams[i]->GetViewMatrix();

			for (auto matInfo : m_renderQueue)
			{
				const uint32 mat = matInfo.first;
				std::map < uint32, std::vector<Transform>>& renderList = matInfo.second;
				Material* material = matManager->GetMaterial(mat);
				material->PrepareForDrawing();
				Shader* shader = material->m_shader;
				int32 proj = glGetUniformLocation(shader->GetShaderID(), "projection");
				int32 view = glGetUniformLocation(shader->GetShaderID(), "view");
				glUniformMatrix4fv(proj, 1, false, glm::value_ptr(projectionMatrix));
				glUniformMatrix4fv(view, 1, false, glm::value_ptr(viewmatrix));
				int32 loc = glGetUniformLocation(shader->GetShaderID(), "dl.color");
				glUniform3f(loc, 1.0, 1.0f, 1.0f);
				loc = glGetUniformLocation(shader->GetShaderID(), "dl.direction");
				glUniform3f(loc, 0.0f, -1.0f, 0.0f);
				myLight->TmpSetUp(shader);

				for (auto& meshInfo : renderList)
				{
					uint32 meshID = meshInfo.first;
					Mesh* mesh = meshManager->GetMesh(meshID);
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
						auto test = glm::value_ptr(modelMat);


						glUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(modelMat));

						glDrawElements(GL_TRIANGLES, mesh->GetIndiceCount(), GL_UNSIGNED_INT, nullptr);

					}
					mesh->UnPrepForDrawing();
				}

				material->Unprep();
			}

		}
		m_renderQueue.clear();
		m_cams.clear();
	}

}