#include "SphereCollider.h"

using namespace ECS;

void SphereCollider::OnInitialise()
{
	// SphereCollider-specific initialisation logic
	std::cout << "Initialising SphereCollider Component" << std::endl;
}

bool SphereCollider::Colliding(SphereCollider& other, glm::vec3& dir)
{
	//takes in another sphere collider and checks for collision
	// return true if collision
	// also find direction vector from this to other
	// Collision detection logic
	return false; // Placeholder return value
}

glm::vec3 SphereCollider::GetCenter()
{
	return _center + _offset; 
}