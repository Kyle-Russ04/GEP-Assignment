#pragma once

#include <iostream>
#include <memory>


namespace ECS
{
	//should be able to expand functionality by creating new component types
	//be easily attached to an entity
	struct Entity;
	struct Core;

	struct Component
	{
		public:
		//data
		bool m_isAlive;
		std::weak_ptr<Entity> m_ParentEntity;

		//functions/methods
		Component();
		~Component();

		void Initialise();
		void Update(float deltaTime);
		void Draw();
		void Kill();
		bool IsAlive();

		//virtual methods to be overridden by derived components
		virtual void OnInitialise();
		virtual void OnUpdate(float deltaTime);
		virtual void OnDraw();
		virtual void OnKill();

		//get entity will call m_parentEntity.lock()
		std::shared_ptr<Entity> GetEntity()
		{
			return m_ParentEntity.lock();
		}

	};

}