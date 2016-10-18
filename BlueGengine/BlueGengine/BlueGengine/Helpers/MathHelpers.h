#pragma once
#include <glm/glm.hpp>
#include "../GlmTransformationInclude.h"
#include <glm/gtc/quaternion.hpp>


inline glm::vec3 QuatToEularAngles(glm::quat& const a_rotation)
{
	return glm::eulerAngles(a_rotation);
}

inline glm::quat QuatFromEular(glm::vec3& const a_vec)
{
	return glm::quat(a_vec);
}

inline glm::mat4 ConvertToLocalSpace(glm::mat4& a_matToConvert, glm::mat4& a_relativeTo)
{
	return glm::inverse(a_relativeTo) * a_matToConvert;
}