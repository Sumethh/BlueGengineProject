#pragma once
#include "BlueCore/Core/Types.h"
#include "BlueCore/Components/ComponentTypes.h"
#include "BlueCore/Serialization/Stencil/Stencil.h"
#include <vector>

namespace Blue
{
	class StencilCreator
	{
	public:
		void Update();

		static StencilCreator* GI()
		{
			if (!mInstance)
			{
				mInstance = new StencilCreator();
			}
			return mInstance;
		}

	private:

		bool mOpened;
		int mCurrentSelectedComponent;
		std::vector<const char*> mCurrentAddedComponents;

		Stencil mCurrentStencil;

		StencilCreator();
		~StencilCreator();
		static StencilCreator* mInstance;
	};
}