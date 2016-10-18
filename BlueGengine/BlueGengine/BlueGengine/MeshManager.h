#pragma once
#include "NonCopyable.h"
#include <vector>
#include "Types.h"
namespace BlueGengine
{
	class Mesh;
	class MeshManager : NonCopyable
	{
		public:

		Mesh* CreateMesh();

		inline Mesh* GetMesh(uint32 a_meshID) const { return m_meshList[a_meshID]; }

		static inline MeshManager* GI()
		{
			if (!m_instance) { m_instance = new MeshManager; }
			return m_instance;
		}

		private:
		MeshManager() {};
		~MeshManager();
		static MeshManager* m_instance;
		std::vector<Mesh*> m_meshList;
	};

}