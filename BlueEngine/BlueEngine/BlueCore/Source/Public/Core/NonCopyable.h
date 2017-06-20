#pragma once
#include "Defines.h"

namespace Blue
{
	class NonCopyable
	{
	protected:
		NonCopyable() {};
		~NonCopyable() {};
	private:
		NonCopyable(const NonCopyable&) = delete;
		const NonCopyable& operator = (const NonCopyable&) = delete;
	};
}