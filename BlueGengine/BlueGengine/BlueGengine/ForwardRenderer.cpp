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
namespace BlueGengine
{
	void ForwardRenderer::SubmitMesh(Mesh* a_mesh, Material* a_material, Transform* a_transform)
	{
		uint32 meshID = a_mesh->GetID();
		uint32 materialID = a_material->GetID();

		m_renderQueue[materialID][meshID].push_back(a_transform);
	}

	void ForwardRenderer::Flush()
	{
		MaterialManager* matManager = MaterialManager::GI();
		MeshManager* meshManager = MeshManager::GI();

		for (auto matInfo : m_renderQueue)
		{
			const uint32 mat = matInfo.first;
			std::map < uint32, std::vector<Transform*>>& renderList = matInfo.second;
			Material* material = matManager->GetMaterial(mat);
			Shader* shader = material->m_shader;
			material->PrepareForDrawing();
			int32 proj = glGetUniformLocation(shader->GetShaderID(), "projection");
			int32 view = glGetUniformLocation(shader->GetShaderID(), "view");
			glUniformMatrix4fv(proj, 1, false, glm::value_ptr(*projMat));
			glUniformMatrix4fv(view, 1, false, glm::value_ptr(*viewMat));
			int32 loc = glGetUniformLocation(shader->GetShaderID(), "dl.color");
			glUniform3f(loc, 1.0, 1.0f, 1.0f);
			loc = glGetUniformLocation(shader->GetShaderID(), "dl.direction");
			glUniform3f(loc, 0.0f, -1.0f, 0.0f);
			myLight->TmpSetUp(shader);
			for (auto& meshInfo : renderList)
			{
				uint32 meshID = meshInfo.first;
				Mesh* mesh = meshManager->GetMesh(meshID);
				std::vector<Transform*>& transforms = meshInfo.second;
				mesh->PrepForDrawing();
				for (auto& transform : transforms)
				{
					glm::mat4 modelMat;
					modelMat = glm::translate(modelMat, transform->pos);
					modelMat = glm::scale(modelMat, transform->scale);
					glm::quat q(transform->rotation);
					modelMat *= glm::mat4_cast(q);

					if (transform->parent)
					{
						glm::mat4 parentModelMat;
						parentModelMat = glm::translate(parentModelMat, transform->parent->pos);
						parentModelMat = glm::scale(parentModelMat, transform->parent->scale);
						glm::quat pq(transform->parent->rotation);
						parentModelMat *= glm::mat4_cast(pq);
						modelMat = parentModelMat * modelMat;
					}

					int32 modelLoc = glGetUniformLocation(shader->GetShaderID(), "model");


					glUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(modelMat));

					glDrawElements(GL_TRIANGLES, mesh->GetIndiceCount(), GL_UNSIGNED_INT, nullptr);

				}
				transforms.clear();
				meshInfo.second.clear();
				mesh->UnPrepForDrawing();
			}

			material->Unprep();
		}
		m_renderQueue.clear();

	}
}