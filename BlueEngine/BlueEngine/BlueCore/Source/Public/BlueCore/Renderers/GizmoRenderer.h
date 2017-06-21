#pragma once
#include "BlueCore/Core/Types.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

namespace Blue
{
#define MAX_LINE_COUNT 10000

	class Mesh;
	class Material;
	class CameraComponent;
	class GizmoRenderer
	{
	public:
		GizmoRenderer();
		~GizmoRenderer();
		enum EGizmoMode : uint32
		{
			Solid = 0,
			WireFrame,
			Count
		};


		void DrawSphere(glm::vec3 aPosition, glm::vec3 aScale, glm::vec3 aColor, EGizmoMode aMode);
		void DrawCube(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 aColor, EGizmoMode aMode);

		void DrawLine(glm::vec3 aStart, glm::vec3 aEnd, glm::vec3 color);
		void DrawPlane(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 aColor, EGizmoMode aMode);

		void DrawCapsule(glm::vec3 aPosition, glm::vec3 aScale, glm::quat aRotation, glm::vec3 color, EGizmoMode aMode);

		void Begin(CameraComponent* aActiveCamera);
		void Flush();

	private:
		void SetCubeMesh(Mesh* aMesh)
		{
			mCubeMesh = aMesh;
		}
		void SetSphereMesh(Mesh* aMesh)
		{
			mSphereMesh = aMesh;
		}
		void SetPlaneMesh(Mesh* aMesh)
		{
			mPlaneMesh = aMesh;
		}
		void SetCapsuleMesh(Mesh* aMesh)
		{
			mCapsuleMesh = aMesh;
		}

		void RenderLines();

		struct LineRenderInfo
		{
			uint32 lineCount;
			uint32 vaoID;
			uint32 vertexBufferID;
		};
		void CreateLineRenderGraphicsResources(LineRenderInfo& aInfo);

		const float mAlpha = 0.7f;

		Mesh* mCubeMesh;
		Mesh* mSphereMesh;
		Mesh* mPlaneMesh;
		Mesh* mCapsuleMesh;
		Material* mDebugMaterial;
		Material* mDebugMaterialInstanced;

		std::vector<LineRenderInfo> mLineRenderinfo;

		uint32 mColorUniformLoc;
		uint32 mModelLoc;
		uint32 mViewLoc;
		uint32 mProjectionLoc;
	};
}
