#include "Transform.h"

using namespace ECS;

void Transform::OnInitialise()
{
	// Transform-specific initialisation logic
	std::cout << "Initialising Transform Component" << std::endl;
}
void Transform::Translate(const glm::vec3& delta)
{
	_position += delta;
}

glm::vec3 ECS::Transform::GetPosition()
{
	return glm::vec3();
}
