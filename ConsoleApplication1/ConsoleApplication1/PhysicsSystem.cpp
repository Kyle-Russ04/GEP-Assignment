#include "PhysicsSystem.h"
#include "Entity.h"
#include "SphereCollider.h"

using namespace ECS;

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Update(float deltaTime)
{

	//get sphere colliders in scene
	//compare each collider against each other collider for collision
	//if collision detected, resolute collison

	//simple collision detection between sphere colliders
	for (size_t i = 0; i < m_colliders.size(); ++i)
	{
		for (size_t j = 0; j < m_colliders.size(); ++j)
		{
			if (i == j) continue; // Skip self-collision

			glm::vec3 dir;
			if (m_colliders[i]->Colliding(*m_colliders[j], dir))
			{
				std::cout << "Collision detected between collider " << i << " and collider " << j << std::endl;
				// Handle collision response here
				
				//grab the two entities that provide true from the collision
				//grab the transforms
				//create movement away from eachother or stop current movement
				std::shared_ptr<Entity> s1Entity = m_colliders[i]->GetEntity();
				std::shared_ptr<Transform> s1Transform = s1Entity->GetComponent<Transform>();

				std::shared_ptr<Entity> s2Entity = m_colliders[j]->GetEntity();
				std::shared_ptr<Transform> s2Transform = s2Entity->GetComponent<Transform>();


				s1Transform->Translate(dir * 0.5001f);
				s2Transform->Translate(dir * -0.5001f);
			}
		}
	}
}