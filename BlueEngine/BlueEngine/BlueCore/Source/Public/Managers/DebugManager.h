#pragma once
#include "Managers/UpdateableManager.h"
#include "Core/Types.h"


enum class EDebugOptionType : uint8
{
	CheckBox,
	Slider,
	Count
};

struct DebugOptionDefenition
{
	char* debugName;
	EDebugOptionType optionType;
};

struct BoolDebugOptionType : public DebugOptionDefenition
{
	bool value;
};

class DebugManager : public UpdatableManager
{
	public:


	void Update() override;

	DebugOptionDefenition* GetDebugOption(char* aName);
	DebugOptionDefenition* GetDebugOption(uint32 aId);

	sizeInt RegisterDebugOption(DebugOptionDefenition* aDefenition);

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

	bool mOpen;

	std::vector<DebugOptionDefenition*> mRegisteredOptions;

	static DebugManager* mInstance;

};