#pragma once
#include "RendererInterface.h"
#include <map>
#include <vector>
#include "Types.h"
#include "GlmTransformationInclude.h"

namespace BlueGengine
{
	class Transform;
	class Light;
	class ForwardRenderer : public IRenderer
	{
		public:
		ForwardRenderer()
		{

		};
		~ForwardRenderer()
		{

		}
		void SubmitMesh(Mesh* a_mesh, Material* a_material, Transform* a_transform) override;

		void Flush()override ;

		glm::mat4* projMat;
		glm::mat4* viewMat;
		Light* myLight;
		private:
		//TODO: DONT LIKE! CHANGE !!!!!!!!!!!!!!!!
		std::map < uint32, std::map<uint32, std::vector<Transform*>>> m_renderQueue;
	};
}
