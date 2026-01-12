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