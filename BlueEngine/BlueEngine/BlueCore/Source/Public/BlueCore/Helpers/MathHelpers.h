#pragma once
#include <glm/glm.hpp>
#include "BlueCore/Core/GlmTransformationInclude.h"
#include <glm/gtc/quaternion.hpp>
#include<cmath>

namespace Blue
{
	namespace MathHelpers
	{
		static float Epsilon = 0.0001f;
		inline glm::vec3 QuatToRadians(glm::quat& aRotation)
		{
			return glm::eulerAngles(aRotation);
		}

		inline glm::quat QuatFromRadians(glm::vec3 aRadians)
		{
			return glm::quat(aRadians);
		}

		inline glm::quat QuatFromEuler(glm::vec3 aDegrees)
		{
			return glm::quat(glm::radians(aDegrees));
		}


		inline float NormalizeAngle(float aAngle)
		{
			float s = aAngle;

			if (aAngle < 0)
			{
				s = aAngle + 360;
			}

			return s;
		}

		inline glm::vec3 QuatToEuler(glm::quat aQuat)
		{
			return glm::degrees(glm::vec3(atan2(2 * aQuat.x * aQuat.w - 2 * aQuat.y * aQuat.z, 1 - 2 * aQuat.x * aQuat.x - 2 * aQuat.z * aQuat.z),
										  atan2(2 * aQuat.y * aQuat.w - 2 * aQuat.x * aQuat.z, 1 - 2 * aQuat.y * aQuat.y - 2 * aQuat.z * aQuat.z),
										  asin(2 * aQuat.x * aQuat.y + 2 * aQuat.z * aQuat.w)));
		}

		inline glm::mat4 ConvertToLocalSpace(const glm::mat4& aMatToConvert, const glm::mat4& aRelativeTo)
		{
			return glm::inverse(aRelativeTo) * aMatToConvert;
		}

		inline glm::vec3 RoundIfLowerThanEpsilon(glm::vec3 aVec)
		{
			if (aVec.x < Epsilon)
			{
				aVec.x = 0;
			}

			if (aVec.y < Epsilon)
			{
				aVec.y = 0;
			}

			if (aVec.z < Epsilon)
			{
				aVec.z = 0;
			}

			return aVec;
		}
	}
}