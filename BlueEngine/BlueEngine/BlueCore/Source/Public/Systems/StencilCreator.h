#pragma once
#include "Core/Types.h"
#include "Components/ComponentTypes.h"
#include "Serialization/Stencil/Stencil.h"
#include <vector>

class StencilCreator
{
	public:
	void Update();

	static StencilCreator* GI() { if (!mInstance) { mInstance = new StencilCreator(); } return mInstance; }

	private:

	bool mOpened;
	int mCurrentSelectedComponent;
	std::vector<const char*> mCurrentAddedComponents;

	Stencil mCurrentStencil;

	StencilCreator();
	~StencilCreator();
	static StencilCreator* mInstance;
};
