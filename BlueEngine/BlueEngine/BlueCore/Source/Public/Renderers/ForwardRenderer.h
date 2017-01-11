#pragma once
#include "RendererInterface.h"
#include <map>
#include <vector>
#include "Core/Types.h"
#include "Core/GlmTransformationInclude.h"

namespace BlueCore
{
	struct Transform;
	class Light;
	class BLUECORE_API ForwardRenderer : public IRenderer
	{
		public:
		ForwardRenderer();

		~ForwardRenderer()
		{

		}
		void SubmitMesh(Mesh* aMesh, Material* aMaterial, Transform aTransform) override;
		void SubmitCamera(CameraComponent* aCamera) override;
		void Flush()override ;
		private:
		//TODO: DONT LIKE! CHANGE !!!!!!!!!!!!!!!!
		std::map < uint32, std::map<Mesh*, std::vector<Transform>>> mRenderQueue;
		std::vector<CameraComponent*> mCams;
		uint32 mWireframeDebugID;
	};
}
