#include "Entity.h"
#include "Component.h"
#include "Core.h"

namespace ECS
{
	Entity::Entity()
	{
		m_isAlive = true;
	}

	Entity::~Entity()
	{
		//cleanup components
	}

	void Entity::Update(float deltaTime)
	{
		//update all components
		for (Component* component : m_components)
		{
			component->OnUpdate(deltaTime);
		}
	}

	void Entity::Draw()
	{
		//draw all components
		for (Component* component : m_components)
		{
			component->OnDraw();
		}
	}

	void Entity::IsAlive(bool _isAlive)
	{
		m_isAlive = _isAlive;
	}

	void Entity::Kill()
	{
		m_isAlive = false;
		//notify components
		for (Component* component : m_components)
		{
			component->OnKill();
			//m_isAlive = false;
		}
		
		/*if (auto coreShare = m_core.lock())
		{
			coreShare->Stop();
		}*/
	}
}