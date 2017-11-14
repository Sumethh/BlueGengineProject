#pragma once9
#include "BlueCore/Core/Types.h"
#include "BlueCore/graphics/mesh.h"

namespace Blue
{
	class NavMeshGenerator
	{
	public:
		NavMeshGenerator();
		~NavMeshGenerator();

		/* Triangulate a mesh by generating indeces based on the vertices passed in
		 * args: in: a_inVertices: An array of vertices in clockwise or counterclockwise order to be triangulated
		 *       out: out_indeces: A triangulated index array for the given set of vertices
		*/
		static void TriangulateMesh(std::vector<Vertex>& a_inVertices, std::vector<uint32>& out_indeces);

	private:
	};

} // namespace Blue