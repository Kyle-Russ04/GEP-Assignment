#include "PhysicsSystem.h"
#include "Entity.h"

using namespace ECS;

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Update(float deltaTime)
{
	//std::shared_ptr<Entity> s1Entity = (*sphere1)->GetEntity();
	//std::shared_ptr<Transform> s1Transform = s1Entity->GetComponent<Transform>();

	//std::shared_ptr<Entity> s2Entity = (*sphere2)->GetEntity();
	//std::shared_ptr<Transform> s2Transform = s2Entity->GetComponent<Transform>();


	//s1Transform->Translate(dir * 0.5001f);
	//s2Transform->Translate(dir * -0.5001f);

	////simple collision detection between sphere colliders
	//for (size_t i = 0; i < m_colliders.size(); ++i)
	//{
	//	for (size_t j = i + 1; j < m_colliders.size(); ++j)
	//	{
	//		glm::vec3 dir;
	//		if (m_colliders[i]->Colliding(*m_colliders[j], dir))
	//		{
	//			std::cout << "Collision detected between collider " << i << " and collider " << j << std::endl;
	//			// Handle collision response here
	//		}
	//	}
	//}
}