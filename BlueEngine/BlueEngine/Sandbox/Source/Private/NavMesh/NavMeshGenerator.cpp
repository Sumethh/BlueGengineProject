#include "NavMesh/NavMeshGenerator.h"
#include "BlueCore/Core/Log.h"

namespace Blue
{
	// Helper Functions
	bool IsConvexMesh(std::vector<Vertex>& a_inVertices)
	{
		BlueAssert(a_inVertices.size() >= 3);
		
		int32 prevZcross = 0;
		for (int i = 0; i < a_inVertices.size() - 2; i++)
		{
			glm::vec3 edge1 = a_inVertices[i + 1].position - a_inVertices[i].position;
			glm::vec3 edge2 = a_inVertices[i + 2].position - a_inVertices[i + 1].position;
			int32 zcross = (edge1.x * edge2.z) - (edge1.z * edge2.x);

			if ((zcross > 0 && prevZcross < 0)
				|| (zcross < 0 && prevZcross > 0))
				return false;

			prevZcross = zcross;
		}

		// All points have <180 angles, making the mesh convex
		return true;
	}

	NavMeshGenerator::NavMeshGenerator()
	{
	}

	NavMeshGenerator::~NavMeshGenerator()
	{
	}

	void NavMeshGenerator::TriangulateMesh(std::vector<Vertex>& a_inVertices, std::vector<uint32>& out_indeces)
	{
		if (a_inVertices.size() < 3)
		{
			Blue::Log::Info(Blue::Logger("Triangulation failed: Number of vertices too low (") << a_inVertices.size() << ")");
			BlueAssert(false);
		}

		if (IsConvexMesh(a_inVertices))
		{
			// Create a simple hull
			// First vertex will be fan point
			for (int i = 1; i < a_inVertices.size() - 1; i++)
			{
				out_indeces.push_back(0);
				out_indeces.push_back(i);
				out_indeces.push_back(i + 1);
			}
		}
		else
		{
			
		}
	}

} // namespace Blue