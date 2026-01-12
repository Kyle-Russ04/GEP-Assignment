#pragma once
#include <vector>
#include <memory>
#include <iostream>

namespace ECS
{
	struct Core;
	struct Component;

	//an entity is a container for components
	//needs to store components
	//needs to allow adding/removing components



	struct Entity
	{
		//for creating new components
		template <typename T> std::shared_ptr<T> AddComponent()
		{
			//static assert to ensure T is derived from Component
			static_assert(std::is_base_of<Component, T>::value, "Error: Entity::AddComponent - T must be derived from Component");

			//create shared ptr of component
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->m_ParentEntity = m_self;

			//initialise component
			rtn->OnInitialise();
			//add to component list
			m_components.push_back(rtn);
			//return component
			return rtn;
		}

		//for retrieving existing components
		template <typename T> std::shared_ptr<T> GetComponent()
		{
			//compiletime sanity check
			static_assert(std::is_base_of<Component, T>::value, "Error: Entity::GetComponent - T must be derived from Component");
			//search through components for type T
			for (int i = 0; i < m_components.size(); i++)
			{
				std::shared_ptr<T> comp = std::dynamic_pointer_cast<T>(m_components[i]);
				if (comp != nullptr)
				{
					return comp;
				}
			}
			return nullptr;
		}

		//data
		std::vector<std::shared_ptr <Component>> m_components;
		bool m_isAlive;

		std::weak_ptr<Core> m_core;
		std::weak_ptr<Entity> m_self;

		//functions
		Entity();
		~Entity();
		void Update(float deltaTime);
		//updating game loop

		void Draw();
		//drawing game loop

		//draw and update need to itterate through components and call their respective functions
		
		void Kill();
		void IsAlive(bool _isAlive);

		std::shared_ptr<Core> GetCore()
		{
			return m_core.lock();
		}
	};

}