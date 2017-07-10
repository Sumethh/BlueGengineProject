#include "BlueCore/Managers/DebugManager.h"
#include "BlueCore/Input/Input.h"
#include <Imgui/imgui.h>
#include "BlueCore/Core/Log.h"
#include <cstring>

namespace Blue
{
	DebugManager* DebugManager::mInstance;



	DebugManager::DebugManager() : UpdatableManager(), mOpen(false)
	{
		BuildTypeHashReference();
	}

	DebugManager::~DebugManager()
	{
	}


	DebugManager::DebugVariableGroup* DebugManager::GetGroupFromName(char* aName)
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
		return currentGroup;
	}

	void DebugManager::DrawGroup(DebugVariableGroup& aGroup)
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader(aGroup.groupName.c_str()))
		{
			for (DebugOptionDefenition& def : aGroup.definitions)
			{
				DrawDebugVariable(def);
			}

			for (DebugVariableGroup& group : aGroup.children)
			{
				DrawGroup(group);
			}
		}
		ImGui::Unindent();
	}

	void DebugManager::DrawDebugVariable(DebugOptionDefenition& aDef)
	{
		switch (aDef.optionType)
		{
			case EDebugOptionType::Bool:
				{
					if (aDef.tweakable)
					{
						ImGui::Checkbox(aDef.debugName, static_cast<bool*>(aDef.variable));
					}
					else
					{
						char* value = *(static_cast<bool*>(aDef.variable)) ? "True" : "False";
						ImGui::Text(aDef.debugName);
						ImGui::SameLine();
						ImGui::Text(": %s", value);
					}
					break;
				}
			case EDebugOptionType::Byte:
				{
					break;
				}
			case EDebugOptionType::UByte:
				{
					break;
				}
			case EDebugOptionType::Int16:
				{
					break;
				}
			case EDebugOptionType::UInt16:
				{
					break;
				}
			case EDebugOptionType::Int32:
				{
					break;
				}
			case EDebugOptionType::UInt32:
				{
					break;
				}
			case EDebugOptionType::Int64:
				{
					break;
				}
			case EDebugOptionType::UInt64:
				{
					break;
				}
			case EDebugOptionType::Float:
				{
					break;
				}
			case EDebugOptionType::Vector2:
				{
					break;
				}
			case EDebugOptionType::Vector3:
				{
					break;
				}
			case EDebugOptionType::Vector4:
				{
					break;
				}
				InvalidDefaultCase
		}
	}

	void DebugManager::Update()
	{
		if (Input::GetKeyPressed(Input::Key::F2))
		{
			mOpen = !mOpen;
		}

		if (mOpen)
		{

			if (ImGui::Begin("Debug Options", &mOpen, ImGuiWindowFlags_NoCollapse))
			{
				for (uint32 i = 0; i < mRoot.children.size(); ++i)
				{
					DrawGroup(mRoot.children[i]);
				}
			}

			ImGui::End();
		}

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
		mHashTypeTable.emplace(typeid(glm::vec2).hash_code(), EDebugOptionType::Vector2);
		mHashTypeTable.emplace(typeid(glm::vec3).hash_code(), EDebugOptionType::Vector3);
		mHashTypeTable.emplace(typeid(glm::vec4).hash_code(), EDebugOptionType::Vector4);
	}
}