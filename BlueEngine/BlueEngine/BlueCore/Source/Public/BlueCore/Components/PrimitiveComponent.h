#pragma once
#include "ActorComponent.h"
#include "BlueCore/Graphics/RenderLayer.h"
#include "BlueCore/Core/Transformable.h"
#include "BlueCore/Core/CapturedPrimitiveData.h"

namespace Blue
{
	class MaterialComponent;
	class Material;

	class PrimitiveComponent : public ActorComponent, public Transformable
	{
	public:
		PrimitiveComponent(Actor* aOwner);
		virtual ~PrimitiveComponent();

		virtual void PostConstruction() override;
		virtual void PreDestruction() override;

		Material* GetMaterial();

		bool IsTranslucent();

		uint64 GetRenderID(const Transform& aInverseCameraTransform);
		virtual void SubmitGeometry(CapturedPrimitiveData& aCapturedData) = 0;
		glm::mat4 GetWorldMatrix();

	private:

		MaterialComponent* mMaterialComponent;
		EFullScreenLayer mFullScreenLayer;
		EViewportLayer mViewportLayer;
	};
}