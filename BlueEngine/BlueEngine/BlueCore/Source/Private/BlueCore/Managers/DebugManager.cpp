#include "BlueCore/Managers/DebugManager.h"
#include "BlueCore/Input/Input.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Utility/Limits.h"

#include <Imgui/imgui.h>
#include <cstring>

namespace Blue
{
	DebugManager* DebugManager::mInstance;

	uint32 uniqueID = 0;

	DebugManager::DebugManager() : UpdatableManager(), mOpen(false)
	{
		BuildTypeHashReference();
	}

	DebugManager::~DebugManager()
	{
	}


	DebugManager::DebugVariableGroup* DebugManager::GetGroupFromName(char* aName, bool& aWasNewlyCreated)
	{
		std::string fullGroupName(aName);
		std::vector<std::string> seperatedGroups;

		while (fullGroupName.size())
		{
			uint64 location = fullGroupName.find_first_of('/');
			if (location != std::string::npos)
			{
				seperatedGroups.emplace_back(fullGroupName.substr(0, location));
				fullGroupName.erase(0, location + 1);
			}
			else
			{
				seperatedGroups.emplace_back(fullGroupName);
				fullGroupName.erase();
			}
		}
		DebugVariableGroup* currentGroup = &mRoot;
		for (uint32 s = 0; s < seperatedGroups.size(); ++s)
		{
			std::string& currentString = seperatedGroups[s];
			bool found = false;
			for (uint32 i = 0; i < currentGroup->children.size(); ++i)
			{
				DebugVariableGroup* checkingGroup = &(currentGroup->children[i]);
				if (currentString == checkingGroup->groupName)
				{
					currentGroup = checkingGroup;
					found = true;
					break;
				}
			}
			if (!found)
			{
				aWasNewlyCreated = true;
				DebugVariableGroup newGroup;
				newGroup.groupName = currentString;
				currentGroup->children.emplace_back(newGroup);
				DebugVariableGroup* currentNewGroup = &currentGroup->children.back();
				for (uint32 j = s + 1; j < seperatedGroups.size(); ++j)
				{
					DebugVariableGroup newChild;
					newChild.groupName = seperatedGroups[j];
					currentNewGroup->children.emplace_back(newChild);
					currentNewGroup = &(currentNewGroup->children.back());
				}
				currentGroup = currentNewGroup;
				break;
			}
		}
		aWasNewlyCreated = false;
		return currentGroup;
	}

	void DebugManager::DrawGroup(DebugVariableGroup& aGroup, std::string& aSearchString)
	{
		std::vector<DebugOptionDefenition*> filteredDefenitionsToRender;
		if (aSearchString.size())
		{
			sizeInt searchStringCount = aSearchString.size();
			for (uint32 i = 0; i < aGroup.definitions.size(); ++i)
			{
				DebugOptionDefenition& def = aGroup.definitions[i];
				if (def.optionType == EDebugOptionType::Space && filteredDefenitionsToRender.size())
				{
					filteredDefenitionsToRender.emplace_back(&aGroup.definitions[i]);
					continue;
				}
				std::string defName(def.debugName);
				sizeInt defNameLength = defName.size();
				if (searchStringCount > defNameLength)
					continue;
				bool add = true;
				for (uint32 s = 0; s < searchStringCount; ++s)
				{
					if (defName[s] != aSearchString[s])
					{
						add = false;
						break;
					}
				}

				if (add)
					filteredDefenitionsToRender.emplace_back(&aGroup.definitions[i]);
			}
		}

		ImGui::Indent();
		if (aSearchString.size())
		{
			bool open = true;
			if (filteredDefenitionsToRender.size())
			{
				ImGui::CollapsingHeader(aGroup.groupName.c_str(), &open);
				for (DebugOptionDefenition* def : filteredDefenitionsToRender)
				{
					DrawDebugVariable(*def);
				}
				ImGui::Spacing();
			}
			else
				ImGui::Unindent();

			for (DebugVariableGroup& group : aGroup.children)
			{
				DrawGroup(group, aSearchString);
			}
			return;
		}
		else if (ImGui::CollapsingHeader(aGroup.groupName.c_str()))
		{
			for (DebugOptionDefenition& def : aGroup.definitions)
			{
				DrawDebugVariable(def);
			}
			for (DebugVariableGroup& group : aGroup.children)
			{
				DrawGroup(group, aSearchString);
			}
			ImGui::Spacing();
			ImGui::Unindent();
		}
		else
			ImGui::Unindent();
	}
	template<typename T, typename V>
	void DrawDebugOption(char* aName, V* aVariable, bool aTweakable);

	template<typename T, typename V>
	void DrawDebugOption(char* aName, V* aVariable, bool aTweakable)
	{
		if (aTweakable)
		{
			T value = static_cast<T>(*aVariable);
			if (std::numeric_limits<V>::is_signed && *aVariable < 0)
			{
				value = static_cast<T>((*aVariable) * -1);
				value *= -1;
			}
			ImGui::Text(aName);
			ImGui::SameLine();
			ImGui::PushID(uniqueID);
			ImGui::InputInt("", reinterpret_cast<int32*>(&value));
			ImGui::PopID();
			SetValueToLimits<T, V>(value);
			*aVariable = static_cast<V>(value);
		}
		else
		{
			ImGui::Text(aName);
			ImGui::SameLine();
			T value = static_cast<T>(*aVariable);
			if (std::numeric_limits<V>::is_signed && *aVariable < 0)
			{
				value = static_cast<T>((*aVariable) * -1);
				value *= -1;
			}

			if constexpr(std::numeric_limits<T>::digits <= 32)
			{
				if (std::numeric_limits<T>::is_signed)
					ImGui::Text("%d", value);
				else
					ImGui::Text("%u", value);
			}
			else if (std::numeric_limits<T>::digits == 64 || std::numeric_limits<T>::digits == 63)
			{
				if (std::numeric_limits<T>::is_signed)
					ImGui::Text("%lld", value);
				else
					ImGui::Text("%llu", value);
			}
			else
				BlueAssert(false);
		}
	}

	template<>
	void DrawDebugOption<float, float>(char* aName, float* aVariable, bool aTweakable)
	{
		if (aTweakable)
		{
			ImGui::Text(aName);
			ImGui::SameLine();
			ImGui::PushID(uniqueID);
			ImGui::InputFloat("", aVariable);
			ImGui::PopID();
		}
		else
		{
			ImGui::Text(aName);
			ImGui::SameLine();
			ImGui::Text("%f", *aVariable);
		}
	}

	template<>
	void DrawDebugOption<double, double>(char* aName, double* aVariable, bool aTweakable)
	{
		(void)aTweakable;
		ImGui::Text(aName);
		ImGui::SameLine();
		double value = *aVariable;
		ImGui::Text("%f", value);
	}

	template<>
	void DrawDebugOption<glm::vec2, glm::vec2>(char* aName, glm::vec2* aVariable, bool aTweakable)
	{
		if (aTweakable)
		{
			ImGui::Text(aName);
			ImGui::SameLine();
			ImGui::PushID(uniqueID);
			ImGui::InputFloat2("", &aVariable->x);
			ImGui::PopID();
		}
		else
		{
			ImGui::Text(aName);
			ImGui::SameLine();
			glm::vec2 value = *aVariable;
			ImGui::Text("X:%f, Y:%f", &aVariable->x, &aVariable->y);
		}
	}

	template<>
	void DrawDebugOption<glm::vec3, glm::vec3>(char* aName, glm::vec3* aVariable, bool aTweakable)
	{
		if (aTweakable)
		{
			ImGui::Text(aName);
			ImGui::SameLine();
			ImGui::PushID(uniqueID);
			ImGui::InputFloat3("", &aVariable->x);
			ImGui::PopID();

		}
		else
		{
			ImGui::Text(aName);
			ImGui::SameLine();
			glm::vec3 value = *aVariable;
			ImGui::Text("X:%f, Y:%f, Z:%f", &aVariable->x, &aVariable->y, &aVariable->z);
		}
	}

	template<>
	void DrawDebugOption<glm::vec4, glm::vec4>(char* aName, glm::vec4* aVariable, bool aTweakable)
	{
		if (aTweakable)
		{
			ImGui::Text(aName);
			ImGui::SameLine();
			ImGui::PushID(uniqueID);
			ImGui::InputFloat4("", &aVariable->x);
			ImGui::PopID();
		}
		else
		{
			ImGui::Text(aName);
			ImGui::SameLine();
			glm::vec4 value = *aVariable;
			ImGui::Text("X:%f, Y:%f, Z:%f, W:%f", &aVariable->x, &aVariable->y, &aVariable->z, &aVariable->w);
		}
	}

	void DebugManager::DrawDebugVariable(DebugOptionDefenition& aDef)
	{

		switch (aDef.optionType)
		{
			case EDebugOptionType::Bool:
				{
					if (aDef.tweakable)
					{

						ImGui::Text(aDef.debugName);
						ImGui::SameLine();
						ImGui::Checkbox("", static_cast<bool*>(aDef.variable));
					}
					else
					{
						char* value = *(static_cast<bool*>(aDef.variable)) ? "True" : "False";
						ImGui::Text(aDef.debugName);
						ImGui::SameLine();
						ImGui::Text("%s", value);
					}
					break;
				}
			case EDebugOptionType::Byte:
				{
					DrawDebugOption<int32, byte>(aDef.debugName, static_cast<byte*>(aDef.variable), aDef.tweakable);
					break;
				}
			case EDebugOptionType::UByte:
				{
					DrawDebugOption<int32, ubyte>(aDef.debugName, static_cast<ubyte*>(aDef.variable), aDef.tweakable);
					break;
				}
			case EDebugOptionType::Int16:
				{
					DrawDebugOption<int32, int16>(aDef.debugName, static_cast<int16*>(aDef.variable), aDef.tweakable);
					break;
				}
			case EDebugOptionType::UInt16:
				{
					DrawDebugOption<int32, uint16>(aDef.debugName, static_cast<uint16*>(aDef.variable), aDef.tweakable);
					break;
				}
			case EDebugOptionType::Int32:
				{
					DrawDebugOption<int32, int32>(aDef.debugName, static_cast<int32*>(aDef.variable), aDef.tweakable);
					break;
				}
			case EDebugOptionType::UInt32:
				{
					DrawDebugOption<int32, uint32>(aDef.debugName, static_cast<uint32*>(aDef.variable), aDef.tweakable);
					break;
				}
			case EDebugOptionType::Int64:
				{
					DrawDebugOption<int64, int64>(aDef.debugName, static_cast<int64*>(aDef.variable), false);
					break;
				}
			case EDebugOptionType::UInt64:
				{
					DrawDebugOption<uint64, uint64>(aDef.debugName, static_cast<uint64*>(aDef.variable), false);
					break;
				}
			case EDebugOptionType::Float:
				{
					DrawDebugOption<float, float>(aDef.debugName, static_cast<float*>(aDef.variable), false);
					break;
				}
			case EDebugOptionType::Double:
				{
					DrawDebugOption<double, double>(aDef.debugName, static_cast<double*>(aDef.variable), false);
					break;
				}
			case EDebugOptionType::Vector2:
				{
					DrawDebugOption<glm::vec2, glm::vec2>(aDef.debugName, static_cast<glm::vec2*>(aDef.variable), aDef.tweakable);
					break;
				}
			case EDebugOptionType::Vector3:
				{
					DrawDebugOption<glm::vec3, glm::vec3>(aDef.debugName, static_cast<glm::vec3*>(aDef.variable), aDef.tweakable);

					break;
				}
			case EDebugOptionType::Vector4:
				{
					DrawDebugOption<glm::vec4, glm::vec4>(aDef.debugName, static_cast<glm::vec4*>(aDef.variable), aDef.tweakable);

					break;
				}
			case EDebugOptionType::Space:
				{
					ImGui::Spacing();
					break;
				}
				InvalidDefaultCase
		}
		++uniqueID;
	}

	void DebugManager::Update()
	{
		if (Input::GetKeyPressed(Input::Key::F2))
		{
			mOpen = !mOpen;
		}

		static char searchString[64] = {};

		if (mOpen)
		{
			if (ImGui::Begin("Debug Options", &mOpen, ImGuiWindowFlags_NoCollapse))
			{
				if (ImGui::IsWindowFocused() && Input::GetKeyDown(Input::Key::LEFT_CONTROL) && Input::GetKeyDown(Input::Key::F))
					ImGui::SetKeyboardFocusHere();
				ImGui::InputText("Search", searchString, sizeof(searchString));
				std::string searchingString(searchString);
				for (uint32 i = 0; i < mRoot.children.size(); ++i)
				{
					DrawGroup(mRoot.children[i], searchingString);
				}
			}

			ImGui::End();
			uniqueID = 0;
		}
	}

	void DebugManager::BeginDebugGroup(char* aGroupName)
	{
		assert(!mCurrentGroup);
		bool isNewGroup = false;
		mCurrentGroup = GetGroupFromName(aGroupName, isNewGroup);

		if (!isNewGroup)
		{
			DebugOptionDefenition def;
			def.optionType = EDebugOptionType::Space;
			mCurrentGroup->definitions.push_back(def);
		}
	}

	void DebugManager::EndDebugGroup()
	{
		assert(mCurrentGroup);
		mCurrentGroup = nullptr;
	}

	void DebugManager::BuildTypeHashReference()
	{
		mHashTypeTable.emplace(typeid(bool).hash_code(), EDebugOptionType::Bool);
		mHashTypeTable.emplace(typeid(byte).hash_code(), EDebugOptionType::Byte);
		mHashTypeTable.emplace(typeid(ubyte).hash_code(), EDebugOptionType::UByte);
		mHashTypeTable.emplace(typeid(int16).hash_code(), EDebugOptionType::Int16);
		mHashTypeTable.emplace(typeid(uint16).hash_code(), EDebugOptionType::UInt16);
		mHashTypeTable.emplace(typeid(int32).hash_code(), EDebugOptionType::Int32);
		mHashTypeTable.emplace(typeid(uint32).hash_code(), EDebugOptionType::UInt32);
		mHashTypeTable.emplace(typeid(int64).hash_code(), EDebugOptionType::Int64);
		mHashTypeTable.emplace(typeid(uint64).hash_code(), EDebugOptionType::UInt64);
		mHashTypeTable.emplace(typeid(float).hash_code(), EDebugOptionType::Float);
		mHashTypeTable.emplace(typeid(double).hash_code(), EDebugOptionType::Double);
		mHashTypeTable.emplace(typeid(glm::vec2).hash_code(), EDebugOptionType::Vector2);
		mHashTypeTable.emplace(typeid(glm::vec3).hash_code(), EDebugOptionType::Vector3);
		mHashTypeTable.emplace(typeid(glm::vec4).hash_code(), EDebugOptionType::Vector4);
	}

	DebugManager::DebugVariableGroup* DebugManager::FindGroupWithVariable(void* aVariable, DebugVariableGroup* aGroup)
	{
		for (sizeInt i = 0; i < aGroup->definitions.size(); ++i)
		{
			if (aGroup->definitions[i].variable == aVariable)
			{
				return aGroup;
			}
		}

		for (sizeInt i = 0; i < aGroup->children.size(); ++i)
		{
			DebugVariableGroup* returnedVal = FindGroupWithVariable(aVariable, &(aGroup->children[i]));
			if (returnedVal)
				return returnedVal;
		}
		return nullptr;
	}

}