#pragma once
#include <vector>
#include "NonCopyable.h"
#include "Types.h"
namespace BlueGengine
{
	class Material;
	class MaterialManager : NonCopyable
	{
		public:


		Material* CreateMaterial();


		inline Material* GetMaterial(const uint32 a_matIndex) { return m_materials[a_matIndex]; }

		static inline MaterialManager* GI()
		{
			if (!m_instance)
			{
				m_instance = new MaterialManager();
			}
			return m_instance;
		}

		private:
		MaterialManager() {};
		~MaterialManager();
		static MaterialManager* m_instance;
		std::vector<Material*> m_materials;
	};
};