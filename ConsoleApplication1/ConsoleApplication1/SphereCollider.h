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

		bool CollidingAABB(const glm::vec3& boxMin, const glm::vec3& boxMax, glm::vec3& dir, float* outPenetration = nullptr);

		float _radius;
		glm::vec3 _center;
		glm::vec3 _offset;
		glm::vec3 position;
	};
}

