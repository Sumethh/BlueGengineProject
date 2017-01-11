#include "Core/Log.h"
#include "Systems/TaskSystem.h"
#include "Systems/Console.h"
#include <MoodyCamel/concurrentqueue.h>
#include <iostream>
#include <fstream>
#include "Core/Timer.h"
namespace BlueCore
{

	moodycamel::ConcurrentQueue<std::string> sStringsToWriteToFile;

	struct LogFileWritingTask : public TaskSystem::ITask
	{
		LogFileWritingTask(char* aFileName) : TaskSystem::ITask(false)
		{
			file.open(aFileName, std::ios::out | std::ios::app | std::ios::trunc);
		}
		~LogFileWritingTask() { file.close(); };

		virtual void Run() override
		{
			std::string stringToWrite;

			while (sStringsToWriteToFile.try_dequeue(stringToWrite))
			{
				file << stringToWrite << std::endl;
			}
		}

		virtual bool IsCompleted() { return false; }

		std::ofstream file;
	};

	void Log::Init(char* aFileName)
	{
		Timer t;
		t.Start();
		LogFileWritingTask* task = new LogFileWritingTask(aFileName);
		TaskSystem::SubmitTask(task);
		auto d = t.IntervalMS();
		LogInfo(std::to_string(d));

	}

	void Log::LogError(std::string aMessage)
	{
		static const std::string errorBase = "[Error] ";
		std::string message = errorBase + aMessage;
		sStringsToWriteToFile.enqueue(message);
		Console::AddLogString(message, Console::ELogType::Error);
	}
	void Log::LogInfo(std::string aMessage)
	{
		static const std::string infoBase = "[Info] ";
		std::string message = infoBase + aMessage;
		sStringsToWriteToFile.enqueue(message);
		Console::AddLogString(message, Console::ELogType::Info);

	}
	void Log::Flush()
	{
		std::cout << std::endl;
	}
}