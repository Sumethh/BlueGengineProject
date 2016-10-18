#pragma once
#include <unordered_map>
namespace BlueGengine
{
	class Mesh;
	class Material;
	class Transform;
	class IRenderer
	{
		public:

		virtual void SubmitMesh(Mesh* a_mesh, Material* a_material, Transform* a_transform) = 0;

		virtual void Flush() = 0;
	};
}