#include "BlueCore/Systems/Console.h"

#include "BlueCore/Input/Input.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Helpers/StringHelpers.h"
#include <vector>
#include <map>

#include <Imgui/imgui.h>

namespace Blue
{
	namespace Console
	{
		const uint32 maxLineCount = 5000;
		bool consoleOpen = false;
		char buffer[500];
		std::string lastInput;
		std::map < std::string, std::vector<std::function<void(std::string&, std::string*, const uint32)>>> commandCallbackMap;


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

			if (entries.size() >= maxLineCount)
			{
				entries.erase(entries.begin());
				entries.emplace_back(std::move(entry));
			}
			else
			{
				entries.emplace_back(std::move(entry));
			}

		}

		void AddCommand(std::string commandBase, std::function<void(std::string, std::string*, const uint32)> aCallBack)
		{
			commandCallbackMap[commandBase].push_back(aCallBack);
		}

		void List(std::string command, std::string* args, const uint32 argCount)
		{
			for (auto& i : commandCallbackMap)
			{
				AddLogString(i.first, Info);
			}
		}

		void Init()
		{
			entries.reserve(maxLineCount);
			std::memset(buffer, 0, sizeof(buffer));
			AddCommand("ListCommands", std::bind(List, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}

		static ImColor white(255, 255, 255, 255);
		static ImColor red(255, 0, 0, 255);
		static ImColor yellow(255, 255, 0);
		void CallCommand(std::string aCommand)
		{
			uint32 spaceCount = StringHelpers::FindCharacterCount(aCommand, ' ');
			size_t firstSpace = aCommand.find(' ', 0);
			std::string command = aCommand.substr(0, firstSpace);

			if (commandCallbackMap.find(command) == commandCallbackMap.end())
			{
				Log::Error(std::string("Could not find command: ") + command);
				return;
			}

			std::string* arguments = new std::string[spaceCount];

			size_t lastOffset = firstSpace;

			for (size_t i = 0; i < spaceCount; ++i)
			{
				size_t spaceOffset = aCommand.find(' ', lastOffset + 1);
				arguments[i] = aCommand.substr(lastOffset + 1, spaceOffset - lastOffset - 1);
				lastOffset = spaceOffset;
			}

			std::vector<std::function<void(std::string&, std::string*, const uint32)>>& callbacks = commandCallbackMap[command];

			for (size_t i = 0; i < callbacks.size(); i++)
			{
				callbacks[i](command, arguments, spaceCount);
			}
		}

		void Update()
		{
			bool setFocus = false;
			bool clearBuffer = false;

			if (Input::GetKeyPressed(Input::Key::GRAVE_ACCENT))
			{
				consoleOpen = !consoleOpen;
				setFocus = true;
			}

			if (consoleOpen)
			{
				if (Input::GetKeyPressed(Input::Key::ENTER))
				{
					std::string string(buffer);

					if (string.size())
					{
						Log::Info(string);
						setFocus = true;
						clearBuffer = true;
					}

					CallCommand(string);
					lastInput = string;
				}

				ImGui::Begin("Console", nullptr, ImVec2(800, 600), 1.0f);

				ImGui::BeginChild("text", ImVec2(ImGui::GetWindowContentRegionWidth(), 540));
				{
					for (size_t i = 0; i < entries.size(); i++)
					{
						ImColor col =  white;

						if (entries[i].type == ELogType::Warning)
						{
							col = yellow;
						}
						else if (entries[i].type == ELogType::Error)
						{
							col = red;
						}

						ImGui::TextColored(col, entries[i].string.c_str());
					}

					if (setFocus)
					{
						ImGui::SetScrollHere();
					}

				}
				ImGui::EndChild();
				ImGuiInputTextFlags flags = ImGuiInputTextFlags_AlwaysInsertMode;

				if (Input::GetKeyPressed(Input::Key::UP))
				{
					std::memset(buffer, 0, sizeof(buffer));
					const char* data = lastInput.c_str();
					std::memcpy(buffer, data, lastInput.size());
					flags |= ImGuiInputTextFlags_ReadOnly;
				}

				ImGui::InputText("Command", buffer, sizeof(buffer), flags);

				if (clearBuffer)
				{
					std::memset(buffer, 0, sizeof(buffer));
				}

				if (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && setFocus)
				{
					ImGui::SetKeyboardFocusHere(0);
				}

				ImGui::End();
			}
		}

		bool IsOpen()
		{
			return consoleOpen;
		}
	}
}