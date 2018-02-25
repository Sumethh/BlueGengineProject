#pragma once
#include "BlueCore/Systems/TaskSystem.h"
#include <Imgui/imgui_impl_glfw_gl3.h>


namespace Blue
{
	struct ImguiInitTask : public TaskSystem::Task
	{
		ImguiInitTask() : TaskSystem::Task("Imgui Init", EThreadType::RenderThread)
		{
		}
		void Run() override
		{
			ImGui_ImplGlfwGL3_Init(window, true);
		}
		bool IsCompleted() override
		{
			return true;
		}

		struct GLFWwindow* window = nullptr;
	};
}  