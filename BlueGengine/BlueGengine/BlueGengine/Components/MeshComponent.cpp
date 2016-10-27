#include "MeshComponent.h"
#include "../Actor.h"
#include "MaterialComponent.h"
#include "TransformComponent.h"
#include "../RendererInterface.h"
#include "../MeshManager.h"
namespace BlueGengine
{

	MeshComponent::MeshComponent(Actor* a_owner) : ActorComponent(a_owner, EComponentType::EMeshComponent)
	{
		m_mesh = MeshManager::GI()->GetMesh(0);
	}

	MeshComponent::~MeshComponent()
	{

	}

	void MeshComponent::BeginPlay()
	{
		m_transformComponent = GetOwner()->GetTransformComponent();
		m_materialComponent = (MaterialComponent*)GetOwner()->GetComponent(EComponentType::EMaterialComponent);

		if (!m_materialComponent)
		{
			Actor* owner = GetOwner();
			owner->AddComponent(EComponentType::EMaterialComponent);
		}
	}

	void MeshComponent::PreRender()
	{
	}

	void MeshComponent::Render(IRenderer* a_renderer)
	{

		a_renderer->SubmitMesh(m_mesh, m_materialComponent->GetMaterial(), m_transformComponent->GetWorldSpaceTransform());

	}

}