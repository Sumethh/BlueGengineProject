#include "Managers/DebugManager.h"
#include "Input/Input.h"

#include "Core/Log.h"
#include <cstring>
DebugManager* DebugManager::mInstance;
DebugManager::DebugManager() : UpdatableManager(), mOpen(false)
{
	int t = 0;
}

DebugManager::~DebugManager()
{

}

void DrawDebugOption(DebugOptionDefenition* aDefenition)
{
	switch (aDefenition->optionType)
	{
		case EDebugOptionType::CheckBox:
			{
				BoolDebugOptionType* optionDef = (BoolDebugOptionType*)aDefenition;
				//ImGui::Checkbox(optionDef->debugName, &optionDef-> value);
			}

		default:
			break;
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

		//if (//ImGui::Begin("Debug Options", &mOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
		{

			for (uint32 i = 0; i < mRegisteredOptions.size(); ++i)
			{
				DrawDebugOption(mRegisteredOptions[i]);
			}
		}

		//ImGui::End();
	}

}

DebugOptionDefenition* DebugManager::GetDebugOption(uint32 aId)
{
	BlueAssert(aId < mRegisteredOptions.size());
	return mRegisteredOptions[aId];
}

DebugOptionDefenition* DebugManager::GetDebugOption(char* aName)
{
	for (uint32 i = 0; i < mRegisteredOptions.size(); ++i)
	{
		if (strcmp(aName, mRegisteredOptions[i]->debugName) == 0)
		{
			return mRegisteredOptions[i];
		}
	}

	return nullptr;
}

sizeInt DebugManager::RegisterDebugOption(DebugOptionDefenition* aDefenition)
{
	sizeInt id = mRegisteredOptions.size();
	mRegisteredOptions.emplace_back(aDefenition);
	return id;
}