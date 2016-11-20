#pragma once
#include "RendererInterface.h"
#include <map>
#include <vector>
#include "../Types.h"
#include "../GlmTransformationInclude.h"

namespace BlueGengine
{
	struct Transform;
	class Light;
	class ForwardRenderer : public IRenderer
	{
		public:
		ForwardRenderer();

		~ForwardRenderer()
		{

		}
		void SubmitMesh(Mesh* aMesh, Material* aMaterial, Transform aTransform) override;
		void SubmitCamera(CameraComponent* aCamera) override;
		void Flush()override ;
		Light* myLight;
		std::vector<Light*> Tlights;
		private:
		//TODO: DONT LIKE! CHANGE !!!!!!!!!!!!!!!!
		std::map < uint32, std::map<Mesh*, std::vector<Transform>>> mRenderQueue;
		std::vector<CameraComponent*> mCams;
	};
}
