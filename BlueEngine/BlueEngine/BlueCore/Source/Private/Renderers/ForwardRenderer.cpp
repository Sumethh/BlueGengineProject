#include "Renderers/ForwardRenderer.h"
#include "Core/Types.h"
#include "Core/Vertex.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Shader.h"
#include "Graphics/Light.h"
#include "Managers/MeshManager.h"
#include "Managers/MaterialManager.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Managers/DebugManager.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.inl>
#include <GL/glew.h>


ForwardRenderer::ForwardRenderer()
{
}

ForwardRenderer::~ForwardRenderer()
{

}

void ForwardRenderer::SubmitMesh(Mesh* aMesh, Material* aMaterial, Transform aTransform)
{
}

void ForwardRenderer::SubmitCamera(CameraComponent* aCamera)
{

}

void ForwardRenderer::Flush()
{

}
