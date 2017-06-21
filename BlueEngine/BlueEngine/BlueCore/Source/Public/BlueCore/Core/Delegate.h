#pragma once
#include <vector>
#include <functional>

namespace Blue
{
	template<class T>
	class Delegate
	{
	public:
		Delegate<T>();
		~Delegate<T>();

		void Clear()
		{
			m_functionsToCall.clear();
		}

		Delegate<T>& operator +=(const std::function<void(T&)>& a_other)
		{
			m_functionsToCall.push_back(a_other);
			return *this;
		}
		Delegate<T>& operator -=(const std::function<void(T&)>& a_other)
		{

			for (auto itr = m_functionsToCall.begin(); itr != m_functionsToCall.end(); itr++)
			{
				if ((*itr).target<T>() == a_other.target<T>())
				{
					m_functionsToCall.erase(itr);
					return *this;
				}
			}

			return *this;
		}
		Delegate<T>& operator()(T& a_t)
		{
			for (std::function<void(T&)> func : m_functionsToCall)
			{
				func(a_t);
			}

			return *this;
		}
	private:

		std::vector<std::function<void(T&)>> m_functionsToCall;


	};

	template<class T>
	Delegate<T>::Delegate()
	{
	}
	template<class T>
	Delegate<T>::~Delegate()
	{

	}
}