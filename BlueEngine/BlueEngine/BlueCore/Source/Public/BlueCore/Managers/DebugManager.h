#pragma once
#include "BlueCore/Managers/UpdateableManager.h"
#include "BlueCore/Core/Types.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <map>


namespace Blue
{
	enum class EDebugOptionType : uint8
	{
		Bool,
		Byte,
		UByte,
		Int16,
		UInt16,
		Int32,
		UInt32,
		Int64,
		UInt64,
		Float,
		Double,
		Vector2,
		Vector3,
		Vector4,
		Space
	};
	class DebugManager : public UpdatableManager
	{
		struct DebugOptionDefenition
		{
			DebugOptionDefenition() : debugName("Default"), optionType(EDebugOptionType::Byte), tweakable(false) { };

			char* debugName;
			EDebugOptionType optionType;
			void* variable;
			bool tweakable;
		};
		struct DebugVariableGroup
		{
			std::string groupName;
			std::vector<DebugOptionDefenition> definitions;
			DebugVariableGroup* mParent;
			std::vector<DebugVariableGroup> children;
		};

	public:

		void Update() override;

		template<typename T>
		void RegisterDebugVariable(T* aVariable, char* aName, bool aTweakable);
		template<typename T>
		void DeregisterDebugVariable(T* aVariable);

		void BeginDebugGroup(char* aGroupName);
		void EndDebugGroup();

		static DebugManager* GI()
		{
			if (mInstance == nullptr)
			{
				mInstance = new DebugManager();
			}

			return mInstance;
		}
	private:

		DebugManager();
		~DebugManager();

		template <typename T>
		EDebugOptionType GetDebugTypeFromType();
		DebugVariableGroup* GetGroupFromName(char* aName, bool& aWasNewlyCreated);
		void DrawGroup(DebugVariableGroup& aGroup, std::string& aSearchString);
		void DrawDebugVariable(DebugOptionDefenition& aDef);
		void BuildTypeHashReference();
		DebugVariableGroup* FindGroupWithVariable(void* aVariable, DebugVariableGroup* aGroup);

		bool mOpen;
		std::map<uint64, EDebugOptionType> mHashTypeTable;

		DebugVariableGroup* mCurrentGroup;

		DebugVariableGroup mRoot;
		static DebugManager* mInstance;
	};

	template < typename T>
	void DebugManager::RegisterDebugVariable(T* aVariable, char* aName, bool aTweakable)
	{
		BlueAssert(mCurrentGroup);
		DebugOptionDefenition variableDef;
		variableDef.debugName = aName;
		variableDef.optionType = GetDebugTypeFromType<T>();

		if constexpr(!std::is_const<T>::value)
		{
			variableDef.tweakable = aTweakable;
			variableDef.variable = static_cast<void*>(aVariable);
		}
		else
		{
			variableDef.variable = (void*)(aVariable);
		}
		mCurrentGroup->definitions.emplace_back(std::move(variableDef));
	}

	template <typename T>
	void DebugManager::DeregisterDebugVariable(T* aVariable)
	{
		DebugVariableGroup* group = FindGroupWithVariable((void*)aVariable, &mRoot);
		if (group)
		{
			for (auto i = group->definitions.begin(); i != group->definitions.end(); ++i)
			{
				if (i->variable == (void*)aVariable)
				{
					group->definitions.erase(i);
					return;
				}
			}
		}
		else
			BlueAssert(false);
	}

	template <typename T>
	EDebugOptionType DebugManager::GetDebugTypeFromType()
	{
		static uint64 hashCode = typeid(T).hash_code();
		BlueAssert(mHashTypeTable.find(hashCode) != mHashTypeTable.end());
		return mHashTypeTable[hashCode];
	}

}



#define BEGIN_DEBUG_GROUP(GroupName) Blue::DebugManager::GI()->BeginDebugGroup(GroupName)
#define END_DEBUG_GROUP() Blue::DebugManager::GI()->EndDebugGroup()

#define ADD_DEBUG_WATCHABLE(Variable) Blue::DebugManager::GI()->RegisterDebugVariable(&Variable, #Variable, false)
#define ADD_DEBUG_TWEAKABLE(Variable) Blue::DebugManager::GI()->RegisterDebugVariable(&Variable, #Variable, true)

#define REMOVE_DEBUG_VARIABLE(Variable) Blue::DebugManager::GI()->DeregisterDebugVariable(&Variable);