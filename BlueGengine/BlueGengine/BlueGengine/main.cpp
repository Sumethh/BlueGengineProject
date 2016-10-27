#include "Temp/VulkanApp.h"
#include "GlTemp/OpenGlApp.h"
#include "Application.h"
#include <vector>

int*** change;

int main(char** args, int argc)
{

	change = new int** [10];
	change[0] = new int* [10];
	change[0][0] = nullptr;
	BlueGengine::Application myApp;
	myApp.Run();

	//	if (1)
	//	{
	//BlueGengine::OpenGLApp openGLApp;
	//openGLApp.Run();
	//	}
	//	else
	//	{
	//		BlueGengine::VulkanApp vulkApp;
	//
	//		vulkApp.Run();
	//	}
}