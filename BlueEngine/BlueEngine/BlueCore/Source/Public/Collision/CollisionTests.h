#pragma once
#include "BoundingVolumes/Sphere.h"
#include "BoundingVolumes/AABB.h"
#include "BoundingVolumes/OBB.h"
#include <glm/glm.hpp>
#include <limits>

const float EPSILON = std::numeric_limits<float>::epsilon();
static inline bool TestColliders(const AABB& aLeft, const AABB aRight)
{
	if (glm::abs(aLeft.position.x - aRight.position.x) > (aLeft.halfExtents.x + aRight.halfExtents.x))
	{
		return false;
	}

	if (glm::abs(aLeft.position.y - aRight.position.y) > (aLeft.halfExtents.y + aRight.halfExtents.y))
	{
		return false;
	}

	if (glm::abs(aLeft.position.z - aRight.position.z) > (aLeft.halfExtents.z + aRight.halfExtents.z))
	{
		return false;
	}

	return true;
}

static inline bool TestColliders(const Sphere& aLeft, const Sphere& aRight)
{
	glm::vec3 distanceBetween = aLeft.position - aRight.position;
	float distSqr = glm::dot(distanceBetween, distanceBetween);
	float sumOfR = aLeft.radius + aRight.radius;
	return distSqr <= sumOfR * sumOfR;
}


static inline bool TestColliders(const OBB& aLeft, const OBB& aRight)
{
	float radiusA, radiusB;
	glm::mat3 rot, absRot;
	glm::vec3 vecBetween = aRight.position - aLeft.position;

	for (uint32 i = 0; i < 3; ++i)
	{
		for (uint32 j = 0; j < 3; ++j)
		{
			rot[i][j] = glm::dot(aLeft.axes[i], aRight.axes[j]);
			absRot[i][j] = glm::abs(rot[i][j]) + EPSILON;
		}
	}

	glm::vec3 t = glm::vec3(glm::dot(vecBetween, aLeft.axes[0]), glm::dot(vecBetween, aLeft.axes[1]), glm::dot(vecBetween, aLeft.axes[2]));

	for (uint32 i = 0; i < 3; ++i)
	{
		radiusA = aLeft.halfExtents[i];
		radiusB = aRight.halfExtents[0] * absRot[i][0] + aRight.halfExtents[1] * absRot[i][1] + aRight.halfExtents[2] * absRot[i][2];

		if (glm::abs(t[i]) > radiusA + radiusB)
		{
			return false;
		}

	}

	for (uint32 i = 0; i < 3; ++i)
	{
		radiusA = aLeft.halfExtents[0] * absRot[i][0] + aLeft.halfExtents[1] * absRot[i][1] + aLeft.halfExtents[2] * absRot[i][2];
		radiusB = aRight.halfExtents[i];

		if (glm::abs(t[0] * rot[0][i] + t[1] * rot[1][i] + t[2] * rot[2][i]) > radiusA + radiusB)
		{
			return false;
		}
	}

	radiusA = aLeft.halfExtents[1] * absRot[2][0] + aLeft.halfExtents[2] * absRot[1][0];
	radiusB = aRight.halfExtents[1] * absRot[0][2] + aRight.halfExtents[2] * absRot[0][1];

	if (glm::abs(t[2] * rot[1][0] - t[1] * rot[2][0]) > radiusA + radiusB)
	{
		return false;
	}

	radiusA = aLeft.halfExtents[1]  * absRot[2][1] +  aLeft.halfExtents[2] * absRot[1][1];
	radiusB = aRight.halfExtents[0] * absRot[0][2] + aRight.halfExtents[2] * absRot[0][0];

	if (glm::abs(t[2] * rot[1][1] - t[1] * rot[2][1]) > radiusA + radiusB)
	{
		return false;
	}

	radiusA = aLeft.halfExtents[1] *  absRot[2][2] + aLeft.halfExtents[2] * absRot[1][2];
	radiusB = aRight.halfExtents[0] * absRot[0][1] + aRight.halfExtents[1] * absRot[0][0];

	if (glm::abs(t[2] * rot[1][2] - t[1] * rot[2][2]) > radiusA + radiusB)
	{
		return false;
	}

	radiusA = aLeft.halfExtents[0] * absRot[2][0] + aLeft.halfExtents[2] * absRot[0][0];
	radiusB = aRight.halfExtents[1] * absRot[1][2] + aRight.halfExtents[2] * absRot[1][1];

	if (glm::abs(t[0] * rot[2][0] - t[2] * rot[0][0]) > radiusA + radiusB)
	{
		return false;
	}


	// Test axis L = A1 x B1
	radiusA = aLeft.halfExtents[0] * absRot[2][1] + aLeft.halfExtents[2] * absRot[0][1];
	radiusB = aRight.halfExtents[0] * absRot[1][2] + aRight.halfExtents[2] * absRot[1][0];

	if (glm::abs(t[0] * rot[2][1] - t[2] * rot[0][1]) > radiusA + radiusB)
	{
		return false;
	}

	// Test axis L = A1 x B2
	radiusA = aLeft.halfExtents[0] * absRot[2][2] + aLeft.halfExtents[2] * absRot[0][2];
	radiusB = aRight.halfExtents[0] * absRot[1][1] + aRight.halfExtents[1] * absRot[1][0];

	if (glm::abs(t[0] * rot[2][2] - t[2] * rot[0][2]) > radiusA + radiusB)
	{
		return false        ;
	}

	// Test axis L = A2 x B0
	radiusA = aLeft.halfExtents[0] * absRot[1][0] + aLeft.halfExtents[1] * absRot[0][0];
	radiusB = aRight.halfExtents[1] * absRot[2][2] + aRight.halfExtents[2] * absRot[2][1];

	if (glm::abs(t[1] * rot[0][0] - t[0] * rot[1][0]) > radiusA + radiusB)
	{
		return false;
	}

	// Test axis L = A2 x B1
	radiusA = aLeft.halfExtents[0] * absRot[1][1] + aLeft.halfExtents[1] * absRot[0][1];
	radiusB = aRight.halfExtents[0] * absRot[2][2] + aRight.halfExtents[2] * absRot[2][0];

	if (glm::abs(t[1] * rot[0][1] - t[0] * rot[1][1]) > radiusA + radiusB)
	{
		return false;
	}

	// Test axis L = A2 x B2
	radiusA = aLeft.halfExtents[0] * absRot[1][2] + aLeft.halfExtents[1] * absRot[0][2];
	radiusB = aRight.halfExtents[0] * absRot[2][1] + aRight.halfExtents[1] * absRot[2][0];

	if (glm::abs(t[1] * rot[0][2] - t[0] * rot[1][2]) > radiusA + radiusB)
	{
		return false;
	}

	return true;
}
