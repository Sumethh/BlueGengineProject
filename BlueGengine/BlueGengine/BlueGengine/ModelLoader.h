#pragma once
#include "NonCopyable.h"

namespace BlueGengine
{
	class Mesh;
	class ModelLoader : public NonCopyable
	{
		public:

		static Mesh* LoadModelFromFile(char* a_filePath);

		private:
		ModelLoader();
		~ModelLoader();
	};
}
