#pragma once
#include <vector>
#include "Types.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
namespace BlueGengine
{
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
		void SetCubeMesh(Mesh* aMesh) { mCubeMesh = aMesh; }
		void SetSphereMesh(Mesh* aMesh) { mSphereMesh = aMesh; }
		void SetPlaneMesh(Mesh* aMesh) { mPlaneMesh = aMesh; }
		void SetCapsuleMesh(Mesh* aMesh) { mCapsuleMesh = aMesh; }

		struct GeneralRenderInfo
		{
			glm::mat4 transform;
			glm::vec3 color;
			EGizmoMode mode;
		};

		const float mAlpha = 0.7f;

		Mesh* mCubeMesh;
		Mesh* mSphereMesh;
		Mesh* mPlaneMesh;
		Mesh* mCapsuleMesh;
		Material* mDebugMaterial;

		uint32 mColorUniformLoc;
		uint32 mModelLoc;
		uint32 mViewLoc;
		uint32 mProjectionLoc;
	};
}