#pragma once

#include <vector>
#include <SDL/SDL.h>
#include <iostream>
#include "Transform.h"


namespace ECS
{

	class InputSystem
	{
	public:
		InputSystem();
		~InputSystem();

		//class stores
		std::vector<int> m_keyDown_state; //current state of 'down key' persisting until changes
		std::vector<int> m_keyUp_change; //key released events this frame , cleared in update
		std::vector<int> m_keyDown_change; //key pressed events this frame , cleared in update

		void HandleInput(const SDL_Event& event);
		bool GetKeyState(int keycode); //returns whether key is currently down
		void Quit();
		bool ShouldQuit();

		void Update(SDL_Event event);
		int keycode;

	private:
		bool m_quitRequested = false;
		Transform m_playerTransform;
		
	};

}