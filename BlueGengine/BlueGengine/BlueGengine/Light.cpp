#include "Light.h"
#include "Shader.h"
#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>
namespace BlueGengine
{

	void Light::TmpSetUp(Shader* a_shader)
	{
		uint32 shaderLoc = a_shader->GetShaderID();

		if (true)
		{
			uint32 lightPosLoc = glGetUniformLocation(shaderLoc, "pl.position");
			uint32 lightColorLoc = glGetUniformLocation(shaderLoc, "pl.color");
			uint32 constantLoc = glGetUniformLocation(shaderLoc, "pl.constant");
			uint32 linearLoc = glGetUniformLocation(shaderLoc, "pl.linear");
			uint32 quadraticLoc = glGetUniformLocation(shaderLoc, "pl.quadratic");


			glUniform3f(lightPosLoc, position.x, position.y, position.z);
			glUniform3f(lightColorLoc, color.r, color.g, color.b);
			glUniform1f(constantLoc, (GLfloat).0f);
			glUniform1f(linearLoc, (GLfloat).09);
			glUniform1f(quadraticLoc, (GLfloat).032);

		}
	}

}