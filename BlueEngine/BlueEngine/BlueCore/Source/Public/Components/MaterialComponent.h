#pragma once
#include "ActorComponent.h"

class Material;
class Actor;
class MaterialComponent : public ActorComponent
{
	public:
	MaterialComponent(Actor* aOwner);
	~MaterialComponent();

	uint64 ID() override { return CompileHash("Material Component"); }

	Material* GetMaterial() const { return mMaterial; }

	private:
	Material* mMaterial;
};