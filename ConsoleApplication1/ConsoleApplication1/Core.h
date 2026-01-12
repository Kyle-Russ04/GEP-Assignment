#pragma once
#include <list>
#include <memory>
#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "glew.h"
#include "InputSystem.h"


namespace ECS
{
	struct Entity;
	struct Component;
	//needs to initialise the game
	//carry out the main game loop
	//store entities
	//must use a singleton pattern to ensure only one is made

	struct Core
	{
		//data:	
		std::list<Entity*> m_entities;
		std::weak_ptr<Core> m_self;
		bool isRunning = true;
		SDL_Window* m_window;
		SDL_GLContext m_glcontext;

		//functions:
		Core();
		~Core();

		//static void Init();
		static std::shared_ptr<Core> Initialise();
		
		void Start();
		void Stop();

		std::shared_ptr<Entity> AddEntity();

		bool InitGL();

		InputSystem m_inputSystem;
		
	};

}