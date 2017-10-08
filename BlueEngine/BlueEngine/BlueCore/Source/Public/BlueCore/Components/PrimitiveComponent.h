#pragma once
#include "ActorComponent.h"
#include "BlueCore/Graphics/RenderLayer.h"
#include "BlueCore/Core/Transformable.h"

namespace Blue
{
	class MaterialComponent;
	class Material;
	class IRenderer;

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

		virtual void SubmitGeometry(IRenderer* aRenderer) = 0;

		glm::mat4 GetWorldMatrix();

	private:

		MaterialComponent* mMaterialComponent;
		EFullScreenLayer mFullScreenLayer;
		EViewportLayer mViewportLayer;
	};
}