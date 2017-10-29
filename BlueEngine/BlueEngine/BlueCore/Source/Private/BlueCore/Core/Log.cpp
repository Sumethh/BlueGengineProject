#include "BlueCore/Core/Log.h"
#include "BlueCore/Systems/TaskSystem.h"
#include "BlueCore/Systems/Console.h"
#include <MoodyCamel/concurrentqueue.h>
#include <iostream>
#include <fstream>
#include "BlueCore/Core/Timer.h"

namespace Blue
{
#define LOG_TO_STANDARD_CONSOLE  1

	moodycamel::ConcurrentQueue<std::string> sStringsToWriteToFile;

	struct LogFileWritingTask : public TaskSystem::ITask
	{
		LogFileWritingTask(char* aFileName) : TaskSystem::ITask("Log Writing Task", false)
		{
			file.open(aFileName, std::ios::out | std::ios::app | std::ios::trunc);
		}
		~LogFileWritingTask()
		{
			file.close();
		};

		virtual void Run() override
		{
			std::string stringToWrite;

			while (sStringsToWriteToFile.try_dequeue(stringToWrite))
			{
				file << stringToWrite << std::endl;
			}
		}

		virtual bool IsCompleted()
		{
			return false;
		}

		std::ofstream file;
	};

	void Log::Init(char* aFileName)
	{
		LogFileWritingTask* task = new LogFileWritingTask(aFileName);
		TaskSystem::SubmitTask(task);
	}

	void Log::Error(std::string aMessage)
	{
		static const std::string errorBase = "[Error] ";
		std::string message = errorBase + aMessage;
		sStringsToWriteToFile.enqueue(message);
		Console::AddLogString(message, Console::ELogType::Error);

#if LOG_TO_STANDARD_CONSOLE
		std::cout << message << "\n";
#endif
	}

	void Log::Warning(std::string aMessage)
	{
		static const std::string errorBase = "[Error] ";
		std::string message = errorBase + aMessage;
		sStringsToWriteToFile.enqueue(message);
		Console::AddLogString(message, Console::ELogType::Error);
	}

	void Log::Info(std::string aMessage)
	{
		static const std::string infoBase = "[Info] ";
		std::string message = infoBase + aMessage;
		sStringsToWriteToFile.enqueue(message);
		Console::AddLogString(message, Console::ELogType::Info);

#if LOG_TO_STANDARD_CONSOLE
		std::cout << message << "\n";
#endif
	}
	void Log::Flush()
	{
		std::cout << std::endl;
	}
}