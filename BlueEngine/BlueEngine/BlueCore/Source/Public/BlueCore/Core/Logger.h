#pragma once

namespace Blue
{
	struct Logger
	{
		Logger(const char* aMessage) : mMessage(aMessage) {};
		Logger(std::string aMessage) : mMessage(aMessage) {};

		template<typename T>
		inline Logger& operator << (const T& aLoggingInfo)
		{
			mMessage += " " + std::to_string(aLoggingInfo);
			return *this;
		}

		template<typename T>
		inline Logger& operator << (T* aLoggingInfo)
		{
			mMessage += " " + std::to_string(*aLoggingInfo);
			return *this;
		}

		template<typename T>
		inline Logger& operator << (const T* aLoggingInfo)
		{
			mMessage += " " + std::to_string(*aLoggingInfo);
			return *this;
		}

		std::string& GetLoggedString()
		{
			return mMessage;
		}

		std::string mMessage;
	};

	template <>
	inline Logger& Logger::operator<< (const std::string& aMessage)
	{
		mMessage += " " + aMessage;
		return *this;
	}
	template <>
	inline Logger& Logger::operator<< (char* aMessage)
	{
		mMessage += " " + std::string(aMessage);
		return *this;
	}

	template <>
	inline Logger& Logger::operator<< (const char* aMessage)
	{
		mMessage += " " + std::string(aMessage);
		return *this;
	}
}