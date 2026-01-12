#pragma once
#include <vector>
#include <iostream>
#include <cstdio>
#include "GLM/glm.hpp"
#include "Transform.h"

namespace ECS
{
	struct SphereCollider;
	struct Transform;

	class PhysicsSystem
	{
		PhysicsSystem();
		~PhysicsSystem();

		void Update(float deltaTime);

	private:
		std::vector<std::shared_ptr<SphereCollider>> m_colliders;

	};

}