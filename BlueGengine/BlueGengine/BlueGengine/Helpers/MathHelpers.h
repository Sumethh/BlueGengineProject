#pragma once
#include <glm/glm.hpp>
#include "../GlmTransformationInclude.h"
#include <glm/gtc/quaternion.hpp>
#include<cmath>


inline glm::vec3 QuatToRadians(glm::quat& a_rotation)
{
	return glm::eulerAngles(a_rotation);
}

inline glm::quat QuatFromRadians(glm::vec3 a_radians)
{
	return glm::quat(a_radians);
}

inline glm::quat QuatFromEuler(glm::vec3 a_degrees)
{
	return glm::quat(glm::radians(a_degrees));
}


inline float NormalizeAngle(float a_angle)
{
	float s = a_angle;

	if (a_angle < 0)
	{
		s = a_angle + 360;
	}

	return s;
}

inline glm::vec3 QuatToEuler(glm::quat a_quat)
{
	glm::vec3 rotation;
	a_quat = glm::normalize(a_quat);
	double test = a_quat.x * a_quat.y + a_quat.z * a_quat.w;

	if (test > 0.499)   // singularity at north pole
	{
		rotation.y = 2 * atan2(a_quat.x, a_quat.w);
		rotation.x = glm::pi<float>() / 2;
		rotation.z = 0;
	}
	else if (test < -0.499)   // singularity at south pole
	{
		rotation.x = -glm::pi < float>() / 2;
		rotation.y = -2 * atan2(a_quat.x, a_quat.w);
		rotation.z = 0;
	}
	else
	{
		double sqx = a_quat.x * a_quat.x;
		double sqy = a_quat.y * a_quat.y;
		double sqz = a_quat.z * a_quat.z;
		rotation.y = (float)(atan2(2 * a_quat.y * a_quat.w - 2 * a_quat.x * a_quat.z, 1 - 2 * sqy - 2 * sqz));
		rotation.z = (float)(asin(2 * test));
		rotation.x = (float)(atan2(2 * a_quat.x * a_quat.w - 2 * a_quat.y * a_quat.z, 1 - 2 * sqx - 2 * sqz));
	}

	return glm::degrees(rotation);
}

inline glm::mat4 ConvertToLocalSpace(glm::mat4& a_matToConvert, glm::mat4& a_relativeTo)
{
	return glm::inverse(a_relativeTo) * a_matToConvert;
}