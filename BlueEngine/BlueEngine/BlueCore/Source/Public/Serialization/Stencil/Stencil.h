#pragma once
#include "../ISerializable.h"
#include "Core/Defines.h"
#include "Components/ComponentTypes.h"
#include "Components/TransformComponent.h"
#include <vector>

namespace BlueCore
{
	class Actor;
	class Stencil : public ISerializable
	{
		public:

		Stencil(std ::string aName);
		Stencil(const Stencil& aOther);
		Stencil(const Stencil&& aOther);
		~Stencil();

		void OnSerialize(ArchiveObject* const aArchive)const override;
		virtual void OnDeserialize(ArchiveObject* const aArchive) override;

		void AddComponent(const EComponentType aComponentType);
		bool RemoveComponent(const EComponentType aComponentType);
		bool RemoveComponent(sizeInt aIndex);

		void Stamp(Actor* aActor);

		Transform GetDefaultTransform()const { return mDefaultTransform; }
		void SetDefaultTransform(Transform aTransform) { mDefaultTransform = aTransform; }
		std::string Name()const { return mName; };
		void SetName(std::string aName) { mName = aName; }
		private:

		Transform mDefaultTransform;
		std::vector<EComponentType> mAddedComponents;
		std::string mName;
	};
}

