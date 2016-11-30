#include "Console.h"
#include "../Imgui/imgui.h"
#include <vector>
#include "../Input.h"
namespace BlueGengine
{
	namespace Console
	{
		bool consoleOpen = false;
		char buffer[500];

		struct StringEntry
		{
			ELogType type;
			std::string string;
		};

		std::vector<StringEntry> entries;

		void AddLogString(std::string aString, ELogType aLogType)
		{
			StringEntry entry = {};
			entry.string = aString;
			entry.type = aLogType;
			entries.emplace_back(std::move(entry));
		}

		void Init()
		{
			entries.reserve(1000);
			std::memset(buffer, 0, sizeof(buffer));
		}
		static ImColor white(255, 255, 255, 255);
		static ImColor red(255, 0, 0, 1);
		void Update()
		{
			if (Input::GetKeyPressed(Input::Key::GRAVE_ACCENT))
			{
				consoleOpen = !consoleOpen;
			}

			if (consoleOpen)
			{
				ImGui::SetNextWindowSize(ImVec2(800, 600));
				ImGui::SetNextWindowPos(ImVec2(0, 0));
				ImGui::Begin("Console");

				ImGui::BeginChild("text", ImVec2(ImGui::GetWindowContentRegionWidth(), 540));
				{
					for (int i = 0; i < entries.size(); i++)
					{
						ImColor col = entries[i].type == ELogType::Info ? white : red;
						ImGui::TextColored(col, entries[i].string.c_str());
					}
				}
				ImGui::EndChild();
				ImGui::InputText("", buffer, sizeof(buffer));

				if (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive())
				{
					ImGui::SetKeyboardFocusHere(0);
				}

				if (Input::GetKeyPressed(Input::Key::ENTER))
				{
					std::string string(buffer);

					if (string.size())
					{
						AddLogString(string, ELogType::Info);
						std::memset(buffer, 0, sizeof(buffer));
					}
				}

				ImGui::End();
			}
		}

	}
}
