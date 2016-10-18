#include "VulkanApp.h"

#include <iostream>
#include <functional>
#include <vector>
#include <cstring>

#include "../ApplicationWindow.h"
#include "../Input.h"
#include "../GlmTransformationInclude.h"
#include "../Defines.h"

const uint32 windowWidth = 1280;
const uint32 windowHeight = 720;

const std::vector<const char*> validationLayers =
{
	"VK_LAYER_LUNARG_standard_validation"
};

VkDebugReportCallbackEXT callback;

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

namespace BlueGengine
{

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64 obj, size_t location, int32 code, const char* layerPrefix, const char* msg, void* userData)
	{

		std::cerr << "Validation layer: " << msg << std::endl;

		return VK_FALSE;
	}


	void VulkanApp::Run()
	{
		m_window = ApplicationWindow::Create("VulkanApp", windowWidth, windowHeight, EGraphicsDeviceType::Vulkan);
		InitVulkan();


		while (!m_window->IsCloseRequest())
		{
			m_window->Update();

			if (Input::GetKeyPressed(Input::Key::ESCAPE))
			{
				m_window->Close();
			}
		}

		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(m_instance, "vkDestroyDebugReportCallbackEXT");

		if (func != nullptr)
		{
			func(m_instance, callback, nullptr);
		}

		if (m_surface)
		{
			vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
		}

		if (m_instance)
		{
			vkDestroyInstance(m_instance, nullptr);
		}

		while (true)
		{

		}
	}

	bool CheckValidationLayerSupport()
	{
		uint32 layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers)
		{
			bool layerFound = false;

			for (const auto& layerProp : availableLayers)
			{
				if (strcmp(layerName, layerProp.layerName) == 0)
				{
					layerFound = true;
					break;
				}


			}

			if (!layerFound)
			{
				return false;
			}
		}

		return true;
	}

	void VulkanApp::InitVulkan()
	{
		if (enableValidationLayers && !CheckValidationLayerSupport())
		{
			BlueAssert(false);
		}

		//uint32 vulkExtensions;
		//vkEnumerateInstanceExtensionProperties(nullptr, &vulkExtensions, nullptr);
		//std::cout << vulkExtensions << " extensions supported" << std::endl;


		//VkApplicationInfo appInfo = {};
		//appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		//appInfo.pApplicationName = "BlueGeninge VulkanImp";
		//appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		//appInfo.pEngineName = "BlueGengine";
		//appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		//appInfo.apiVersion = VK_API_VERSION_1_0;

		//VkInstanceCreateInfo  createInfo = {};
		//std::vector<VkExtensionProperties> props(vulkExtensions);
		//vkEnumerateInstanceExtensionProperties(nullptr, &vulkExtensions, props.data());
		//std::vector<char*> extensionNames(vulkExtensions);

		//for (int i = 0; i < vulkExtensions; i++)
		//{
		//	extensionNames[i] = props[i].extensionName;
		//}

		//createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		//createInfo.pApplicationInfo = &appInfo;
		//createInfo.enabledExtensionCount = vulkExtensions;
		//createInfo.ppEnabledExtensionNames = extensionNames.data();

		//if (enableValidationLayers)
		//{
		//	createInfo.enabledLayerCount =  validationLayers.size();
		//	createInfo.ppEnabledLayerNames = validationLayers.data();
		//}
		//else
		//{
		//	createInfo.enabledLayerCount = 0;
		//}

		//VkResult res;
		//res = vkCreateInstance(&createInfo, nullptr, &m_instance);

		//if (res == VK_ERROR_INCOMPATIBLE_DRIVER)
		//{
		//	BlueAssert(false);
		//}
		//else if (res)
		//{
		//	BlueAssert(false);
		//}


		////Create debug validation layers
		//if (enableValidationLayers)
		//{
		//	VkDebugReportCallbackCreateInfoEXT createDebugInfo = {};
		//	createDebugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		//	createDebugInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		//	createDebugInfo.pfnCallback = debugCallback;

		//	//finding the address of callback function
		//	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugReportCallbackEXT");

		//	if (func != nullptr)
		//	{
		//		VkResult res = func(m_instance, &createDebugInfo, NULL, &callback);

		//		if (res != VK_SUCCESS)
		//		{
		//			BlueAssert(false);
		//		}
		//	}
		//}

		////Pick Physical Device
		//uint32 deviceCount = 0;

		//vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

		//if (deviceCount == 0)
		//{
		//	BlueAssert(false);
		//}


		//glfwCreateWindowSurface(m_instance, m_window->GetUnderlyingWindow(), nullptr, &m_surface);


		//std::vector<VkPhysicalDevice> devices(deviceCount);

		//vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());
		//int z = 0;

		//for (const auto& device : devices)
		//{
		//	VkPhysicalDeviceProperties deviceProps;
		//	vkGetPhysicalDeviceProperties(device, &deviceProps);

		//	VkPhysicalDeviceFeatures deviceFeatures;
		//	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		//	if (deviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader)
		//	{
		//		m_physicalDevice = devices[z];
		//		std::cout << "Vendor ID: " << deviceProps.vendorID << std::endl;
		//		std::cout << "Device Name: " << deviceProps.deviceName << std::endl;
		//		std::cout << "Api Version: " << deviceProps.apiVersion << std::endl;
		//		std::cout << "Driver Version: " << deviceProps.driverVersion << std::endl;

		//	}

		//	z++;
		//}

		//if (m_physicalDevice == VK_NULL_HANDLE)
		//{
		//	BlueAssert(false);
		//}

		////check support for queue families
		//int32 graphicsFamily = -1;
		//uint32 queueFamilyCount = 0 ;
		//vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);

		//std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		//vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, queueFamilies.data());

		//for (const auto& queueFamily : queueFamilies)
		//{

		//	if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		//	{
		//		//Our device handles the queues that where want/need!
		//	}

		//	VkBool32 presentSupport = false;

		//	vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, i, m_surface, &presentSupport);

		//	if (queueFamily.queueCount > 0 && presentSupport)
		//	{
		//		presentFamily = i;
		//	}

		//	if (graphicsFamily >= 0 && presentFamily >= 0)
		//	{
		//		break
		//	}

		//	presentFamily = -1;
		//	graphicsFamily = -1;
		//	i++;
		//}

		//float queuePriority = 1.0f;

		//std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		//std::set<int> uniqueQueueFamilies = { graphicsFamily, presentFamily };

		//for (int queueFamily : uniqueQueueFamilies)
		//{
		//	VkDeviceQueueCreateInfo queueCreateInfo = {};
		//	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		//	queueCreateInfo.queueFamilyIndex = queueFamily;
		//	queueCreateInfo.queueCount = 1;
		//	queueCreateInfo.pQueuePriorities = &queuePriority;
		//	queueCreateInfos.push_back(queueCreateInfo);
		//}




	}

}