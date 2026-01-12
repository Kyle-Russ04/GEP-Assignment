#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace ECS
{
	struct Transform : ECS::Component
	{
	public:
		void OnInitialise();
		void Translate(const glm::vec3& delta);
		glm::vec3 GetPosition();

	private:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale{ 1.0f, 1.0f, 1.0f };
	};
}

