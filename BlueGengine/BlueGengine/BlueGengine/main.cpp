#include "Temp/VulkanApp.h"
#include "GlTemp/OpenGlApp.h"
#include "Application.h"
#include "timer.h"
#include <functional>
#include <iostream>
#include "Helpers/MathHelpers.h"
int main(char** args, int argc)
{
	glm::mat4 a;
	a = glm::translate(a, glm::vec3(-1.0f, 0.0f, 0.0f));
	a = glm::rotate(a, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 b;
	b = glm::translate(b, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 local = ConvertToLocalSpace(b, a);



//	BlueGengine::Application myApp;
//	myApp.Run();

	//	if (1)
	//	{
	BlueGengine::OpenGLApp openGLApp;
	openGLApp.Run();
	//	}
	//	else
	//	{
	//		BlueGengine::VulkanApp vulkApp;
	//
	//		vulkApp.Run();
	//	}
}