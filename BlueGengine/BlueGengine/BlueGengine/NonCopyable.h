#pragma once

class NonCopyable
{
protected:
	NonCopyable() {};
	~NonCopyable() {};
private:
	NonCopyable(const NonCopyable&) = delete;
	const NonCopyable& operator = (const NonCopyable&) = delete;
};