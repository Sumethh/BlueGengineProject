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
		Vector2,
		Vector3,
		Vector4
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
		void RegisterDebugVariable(T* aVariable, char* aGroupName, char* aName, bool aTweakable);

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

		DebugVariableGroup* GetGroupFromName(char* aName);
		void DrawGroup(DebugVariableGroup& aGroup);
		void DrawDebugVariable(DebugOptionDefenition& aDef);
		bool mOpen;
		std::map<uint64, EDebugOptionType> mHashTypeTable;

		DebugVariableGroup mRoot;
		static DebugManager* mInstance;
		void BuildTypeHashReference();
	};

	template <typename T>
	void DebugManager::RegisterDebugVariable(T* aVariable, char* aGroupName, char* aName, bool aTwekable)
	{
		DebugVariableGroup* group = GetGroupFromName(aGroupName);
		DebugOptionDefenition variableDef;
		variableDef.debugName = aName;
		variableDef.optionType = GetDebugTypeFromType<T>();
		variableDef.tweakable = aTwekable;
		variableDef.variable = static_cast<void*>(aVariable);
		group->definitions.emplace_back(std::move(variableDef));
	}

	template <typename T>
	EDebugOptionType DebugManager::GetDebugTypeFromType()
	{
		static uint64 hashCode = typeid(T).hash_code();
		BlueAssert(mHashTypeTable.find(hashCode) != mHashTypeTable.end());
		return mHashTypeTable[hashCode];
	}
}





#define ADD_DEBUG_WATCHABLE(Variable, GroupName) Blue::DebugManager::GI()->RegisterDebugVariable(&Variable, GroupName, #Variable, false)
#define ADD_DEBUG_TWEAKABLE(Variable, GroupName) Blue::DebugManager::GI()->RegisterDebugVariable(&Variable, GroupName, #Variable, true)