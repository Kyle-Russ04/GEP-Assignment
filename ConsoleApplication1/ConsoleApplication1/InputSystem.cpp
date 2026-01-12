#include "InputSystem.h"

using namespace ECS;

InputSystem::InputSystem()
	:m_quitRequested(false),
	m_keyDown_state(SDL_NUM_SCANCODES, 0),
	m_keyUp_change(SDL_NUM_SCANCODES, 0),
	m_keyDown_change(SDL_NUM_SCANCODES, 0)
{

}

InputSystem::~InputSystem()
{
}

void InputSystem::HandleInput(const SDL_Event& event)
{
	keycode = event.key.keysym.scancode;
	//handle quit event
	switch (event.type)
	{
		case SDL_QUIT:
			m_quitRequested = true;
			return;
		case SDL_KEYDOWN:
		{
			std::vector<int>::iterator it = std::find(m_keyDown_state.begin(), m_keyDown_state.end(), keycode);
			if (it == m_keyDown_state.end())
			{
				m_keyDown_state.push_back(keycode); //set key as down
				m_keyDown_change[keycode] = 1; //register key down change event
			}
			break;
		}
		case SDL_KEYUP:
		{
			//reove key from down state
			std::vector<int>::iterator it = std::find(m_keyDown_state.begin(), m_keyDown_state.end(), keycode);
			m_keyDown_state.erase(it); //set key as up
			m_keyUp_change[keycode] = 1; //register key up change event
			break;
		}
	}
}

bool InputSystem::GetKeyState(int keycode)
{
	return std::find(m_keyDown_state.begin(), m_keyDown_state.end(), keycode) != m_keyDown_state.end();
}

void ECS::InputSystem::Quit()
{
	m_quitRequested = true;
}

bool ECS::InputSystem::ShouldQuit()
{
	return m_quitRequested;
}

void ECS::InputSystem::Update(SDL_Event event)
{
	int keycode = event.key.keysym.scancode;
	GetKeyState(keycode);


	//clear change states after processing
	std::fill(m_keyDown_change.begin(), m_keyDown_change.end(), 0);
	std::fill(m_keyUp_change.begin(), m_keyUp_change.end(), 0);
}
