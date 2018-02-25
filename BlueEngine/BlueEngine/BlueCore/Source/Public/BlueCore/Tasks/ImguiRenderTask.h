#pragma once
#include <Imgui/imgui.h>
#include <Imgui/imgui_impl_glfw_gl3.h>

namespace Blue
{
	class ImguiRenderTask : public TaskSystem::Task
	{
	public:
		ImguiRenderTask() : TaskSystem::Task("Imgui Render", EThreadType::RenderThread)
		{
		}
		~ImguiRenderTask()
		{
			for (int i = 0; i < drawData.CmdListsCount; ++i)
			{
				delete drawData.CmdLists[i];
			}
		}
		void Run() override
		{
			ImGui_ImplGlfwGL3_RenderDrawLists(&drawData);		
		}
		bool IsCompleted() override
		{
			return true;
		}
		ImDrawData drawData;
	};
}