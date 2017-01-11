#pragma once
#include "Serialization/Stencil/Stencil.h"

#include <map>
namespace BlueCore
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