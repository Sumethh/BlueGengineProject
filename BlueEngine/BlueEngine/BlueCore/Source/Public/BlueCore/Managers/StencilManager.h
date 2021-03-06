#pragma once
#include "BlueCore/Serialization/Stencil/Stencil.h"

#include <map>

namespace Blue
{
	class StencilManager
	{
	public:

		void Init();

		Stencil* GetStencil(std::string stencilName);

	private:
		void CreateStencils(std::vector<std::string>& fileNames);

		std::map<std::string, Stencil*> mStencils;
	};
}