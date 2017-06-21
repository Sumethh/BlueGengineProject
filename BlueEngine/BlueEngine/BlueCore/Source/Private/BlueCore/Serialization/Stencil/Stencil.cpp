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

	}

	Stencil::Stencil(const Stencil&& aOther)
	{

	}

	Stencil::~Stencil()
	{

	}

	void Stencil::OnSerialize(ArchiveObject* const aArchive) const
	{
		BlueAssert(aArchive);
		aArchive->Archive("Stencil Name", mName);
		std::vector<uint32> serializingArray;
		serializingArray.reserve(mAddedComponents.size());
		glm::quat r;
		ArchiveObject transformArchive("Transform");
		transformArchive.Archive("position", mDefaultTransform.position);
		transformArchive.Archive("rotation", mDefaultTransform.rotation);
		transformArchive.Archive("scale", mDefaultTransform.scale);
		aArchive->Archive(&transformArchive);

		for (size_t i = 0; i < mAddedComponents.size(); ++i)
		{
			serializingArray.push_back((uint32)mAddedComponents[i]);
		}

		aArchive->Archive("Components", serializingArray);
	}

	void Stencil::OnDeserialize(ArchiveObject* const aArchive)
	{
		auto archive = aArchive->GetArc();
		mName = archive["Stencil Name"];
		std::vector<int> comps = archive["Components"];


		for (auto co : comps)
		{
			mAddedComponents.push_back((EComponentType)co);
		}

		nlohmann::json transform = archive["Transform"];
		glm::quat r;
		mDefaultTransform.position = glm::vec3(transform["position"]["x"], transform["position"]["y"], transform["position"]["z"]);
		mDefaultTransform.rotation = glm::quat(transform["rotation"]["w"], transform["rotation"]["x"], transform["rotation"]["y"], transform["rotation"]["z"]);
		mDefaultTransform.scale = glm::vec3(transform["scale"]["x"], transform["scale"]["y"], transform["scale"]["z"]);

		int ts = 0;
	}

	void Stencil::AddComponent(const EComponentType aComponent)
	{
		mAddedComponents.emplace_back(aComponent);
	}

	bool Stencil::RemoveComponent(const EComponentType aComponentType)
	{
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