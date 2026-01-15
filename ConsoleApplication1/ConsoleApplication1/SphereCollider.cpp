#include "SphereCollider.h"

using namespace ECS;

void SphereCollider::OnInitialise()
{
	// SphereCollider-specific initialisation logic
	std::cout << "Initialising SphereCollider Component" << std::endl;
}

bool SphereCollider::Colliding(SphereCollider& other, glm::vec3& dir)
{
	// Compute world-space centers (position + local center/offset)
	glm::vec3 thisCenter = position + GetCenter();
	glm::vec3 otherCenter = other.position + other.GetCenter();

	// Vector from this to other
	glm::vec3 delta = otherCenter - thisCenter;

	// Use squared distance to avoid an unnecessary sqrt
	float distSq = glm::dot(delta, delta);
	float radiusSum = _radius + other._radius;
	float radiusSumSq = radiusSum * radiusSum;

	if (distSq <= radiusSumSq)
	{
		// If centers coincide, direction is undefined -> return zero vector
		if (distSq > 0.0f)
			dir = glm::normalize(delta);
		else
			dir = glm::vec3(0.0f);

		return true; // colliding or touching
	}

	// Not colliding
	dir = glm::vec3(0.0f);
	return false;
}

glm::vec3 SphereCollider::GetCenter()
{
	return _center + _offset; 
}

bool SphereCollider::CollidingAABB(const glm::vec3& boxMin, const glm::vec3& boxMax, glm::vec3& dir, float outPenetration)
{
	// world-space sphere center
	glm::vec3 sphereCenter = position + GetCenter();

	// Clamp sphere center to AABB to get the closest point on/in the box
	glm::vec3 closest = glm::clamp(sphereCenter, boxMin, boxMax);

	// Vector from closest point to sphere center
	glm::vec3 delta = sphereCenter - closest;
	float distSq = glm::dot(delta, delta);
	float radius = _radius;
	float radiusSq = radius * radius;

	// Case 1: sphere center is outside or exactly on surface
	if (distSq > 0.0f)
	{
		if (distSq <= radiusSq)
		{
			float dist = std::sqrt(distSq);
			// separation direction points from box to sphere (normalize delta)
			dir = glm::normalize(delta);
			if (outPenetration == radius - dist)
			{
				return true;
			}
		}

		// not colliding
		dir = glm::vec3(0.0f);
		if (outPenetration == 0.0f)
		{
			return false;
		}
	}

	// Case 2: sphere center is inside the AABB (closest == sphereCenter).
	// We must find the shallowest axis to push the sphere out.
	{
		glm::vec3 boxCenter = (boxMin + boxMax) * 0.5f;
		glm::vec3 half = (boxMax - boxMin) * 0.5f;
		glm::vec3 local = sphereCenter - boxCenter;
		glm::vec3 absLocal = glm::abs(local);

		// distances to the faces along each axis
		glm::vec3 distToFace = half - absLocal;

		// find smallest penetration axis
		int axis = 0;
		if (distToFace.y < distToFace.x) axis = 1;
		if (distToFace.z < distToFace[axis]) axis = 2;

		// construct outward normal on that axis
		dir = glm::vec3(0.0f);
		dir[axis] = (local[axis] >= 0.0f) ? 1.0f : -1.0f;

		// penetration is radius plus how far inside the box we are to that face
		float penetrationToFace = distToFace[axis];
		if (outPenetration = radius + penetrationToFace)
		{
			return true;
		}
	}
}