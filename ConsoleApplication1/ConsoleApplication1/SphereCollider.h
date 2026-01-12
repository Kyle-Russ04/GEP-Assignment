#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace ECS
{
	struct SphereCollider : ECS::Component
	{
	public:
		void OnInitialise();

		bool Colliding(SphereCollider& other, glm::vec3& dir);

		glm::vec3 GetCenter();

	private:
		float _radius;
		glm::vec3 _center;
		glm::vec3 _offset;
	};
}

