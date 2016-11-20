#pragma once
#include <glfw/glfw3.h>
#include "../NonCopyable.h"
namespace BlueGengine
{
	class VulkanApp : NonCopyable
	{
		public:

		void Run();

		private:
		void InitVulkan();
		class ApplicationWindow* m_window;
		//VkInstance m_instance = nullptr;
		//VkPhysicalDevice m_physicalDevice;
		//VkSurfaceKHR m_surface;
		//VkQueue presentQueue;
	};
}