#pragma once
#include "BlueCore.h"
#include <vector>
#include "Core/IDelegate.h"

namespace Blue
{
	struct IMessage
	{
	public:
	};

	template<typename T>
	class Message
	{
		using FunctionPointer = void(*)(T*);

	public:
		static void Send(T* aMessage)
		{
			std::vector<IDelegate<void, T*>*>& registeredListeners = GetCallbacks();

			if (registeredListeners.size())
			{
				auto current = registeredListeners.begin();
				auto end = registeredListeners.end();

				while (current != end)
				{
					(*(*current))(aMessage);
					current++;
				}
			}
		}
		static void Listen(FunctionPointer aFunctor)
		{
			GetCallbacks().push_back(new SimpleDelegate<void, T*>(aFunctor));
		}
		template<typename CallingClass>
		static void Listen(CallingClass* aClass, void(CallingClass::*aFunctor)(T*))
		{
			GetCallbacks().push_back(new MemberDelegate<CallingClass, void, T*>(aClass, aFunctor));
		}

	private:
		static std::vector<IDelegate<void, T*>*>& GetCallbacks()
		{
			static std::vector <IDelegate<void, T*>*> callbacks;

			return callbacks;
		}
	};
}