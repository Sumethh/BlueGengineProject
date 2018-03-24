#include "BlueCore/Serialization/Stencil/Stencil.h"
#include "BlueCore/Serialization/ArchiveObject.h"
#include "BlueCore/Core/Actor.h"

namespace Blue
{
	Stencil::Stencil(std::string aName) : mName(aName)
	{

	}

	Stencil::Stencil(const Stencil& aOther)
	{
		(void)aOther;
	}

	Stencil::Stencil(const Stencil&& aOther)
	{
		(void)aOther;
	}

	Stencil::~Stencil()
	{

	}

	void Stencil::OnSerialize(ArchiveObject* const aArchive) const
	{
		(void)aArchive;
		BlueAssert(false);
	}

	void Stencil::OnDeserialize(ArchiveObject* const aArchive)
	{
		(void)aArchive;
		BlueAssert(false);
	}

	void Stencil::AddComponent(const EComponentType aComponent)
	{
		mAddedComponents.emplace_back(aComponent);
	}

	bool Stencil::RemoveComponent(const EComponentType aComponentType)
	{
		(void)aComponentType;
		BlueAssert(false);
		return true;
	}

	bool Stencil::RemoveComponent(size_t aIndex)
	{
		BlueAssert(aIndex < mAddedComponents.size());
		auto it = mAddedComponents.begin() + aIndex;
		mAddedComponents.erase(it);
		return true;
	}

	void Stencil::Stamp(Actor* aActor)
	{
		(void)aActor;
		//aActor->OnConstruct(mAddedComponents.data(), mAddedComponents.size());
		//aActor->GetTransformComponent()->SetTransform(mDefaultTransform);
	}
}