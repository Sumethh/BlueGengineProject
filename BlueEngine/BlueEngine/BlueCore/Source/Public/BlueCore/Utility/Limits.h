#pragma once
#include <limits>

namespace Blue
{

	template<typename V, typename T >
	bool IsValueWithinNumericLimits(V aValue)
	{
		if (aValue < std::numeric_limits<T>::min() || aValue > std::numeric_limits<T>::max())
		{
			return false;
		}
		return true;
	}

	template<typename V, typename T>
	void SetValueToLimits(V& aValue)
	{
		if (aValue > static_cast<T>(std::numeric_limits<T>::max()))
			aValue = static_cast<V>(std::numeric_limits<T>::max());
		else if (aValue < static_cast<T>(std::numeric_limits<T>::min()))
			aValue = static_cast<V>(std::numeric_limits<T>::min());
	}

}