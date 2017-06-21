#pragma once
#include "BlueCore/BlueCore.h"

namespace Blue
{
	template < typename ReturnVal, typename... Arguments>
	class IDelegate
	{
	public:
		IDelegate() = default;
		IDelegate(const  IDelegate&) = default;
		IDelegate(IDelegate&&) = default;
		IDelegate& operator=(const IDelegate&)& = default;
		IDelegate& operator=(IDelegate&&)& = default;
		virtual ~IDelegate() = default;
		virtual ReturnVal operator()(Arguments...) = 0;
	};

	template<typename ReturnVal, typename... Arguments>
	class SimpleDelegate : public IDelegate<ReturnVal, Arguments...>
	{
		using FunctionPointer = ReturnVal(*)(Arguments...);
	public:
		SimpleDelegate(FunctionPointer aFunction) : mFunction(aFunction)
		{
		}

		ReturnVal operator()(Arguments... args) override
		{
			return (*mFunction)(args...);
		}

	private:
		FunctionPointer mFunction;
	};


	template <typename Owner, typename ReturnVal, typename... Arguments>
	class MemberDelegate : public IDelegate<ReturnVal, Arguments...>
	{
		using FunctionPointer = ReturnVal(Owner::*)(Arguments...);
	public:
		MemberDelegate(Owner* aOwner, FunctionPointer aFunction) : mOwner(aOwner), mFunction(aFunction)
		{}

		ReturnVal operator()(Arguments... args) override
		{
			return (mOwner->*mFunction)(args...);
		}

	private:
		Owner* mOwner;
		FunctionPointer mFunction;
	};
}