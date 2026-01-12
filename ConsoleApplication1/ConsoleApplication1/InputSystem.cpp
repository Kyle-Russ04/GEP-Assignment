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
	int keycode = event.key.keysym.scancode;
	//handle quit event
	switch (event.type)
	{
		case SDL_QUIT:
			m_quitRequested = true;
			return;
		case SDL_KEYDOWN:
			if (m_keyDown_state[keycode] == 0)
			{
				m_keyDown_state[keycode] = 1; //set key as down
				m_keyDown_change[keycode] = 1; //register key down change event
			}
			break;
		case SDL_KEYUP:
			if (m_keyDown_state[keycode] == 1)
			{
				m_keyDown_state[keycode] = 0; //set key as up
				m_keyUp_change[keycode] = 1; //register key up change event
			}
			break;
	}

	switch (keycode)
	{
	default:
		break;
	case SDL_SCANCODE_W:
		// Move up
		std::cout << "W key pressed" << std::endl;
		m_playerTransform.Translate(glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case SDL_SCANCODE_S:
		// Move down
		std::cout << "S key pressed" << std::endl;
		m_playerTransform.Translate(glm::vec3(0.0f, -1.0f, 0.0f));
		break;
	case SDL_SCANCODE_A:
		// Move left
		std::cout << "A key pressed" << std::endl;
		m_playerTransform.Translate(glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	case SDL_SCANCODE_D:
		// Move right
		std::cout << "D key pressed" << std::endl;
		m_playerTransform.Translate(glm::vec3(-1.0f, 0.0f, 0.0f));
		break;

	case SDL_SCANCODE_SPACE:
		// Jump
		std::cout << "Space key pressed" << std::endl;
		break;
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
