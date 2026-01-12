#include "Player.h"
#include <iostream>
#include <SDL/SDL.h>

using namespace ECS;

void Player::OnUpdate(float deltaTime)
{
	std::shared_ptr<Core> core = GetEntity()->GetCore();
	std::shared_ptr<InputSystem> inputSystem = core->GetInputSystem();
	std::shared_ptr<Transform> playerTransform = GetEntity()->GetComponent<Transform>();

	// Query the current key state instead of switching on a stored "last key" value.
// This ensures movement stops when the key is released.
	if (inputSystem->GetKeyState(SDL_SCANCODE_W))
	{
		playerTransform->Translate(glm::vec3(0.0f, 0.0f, -0.1f));
		std::cout << "W key pressed" << std::endl;
	}
	if (inputSystem->GetKeyState(SDL_SCANCODE_S))
	{
		playerTransform->Translate(glm::vec3(0.0f, 0.0f, 0.1f));
		std::cout << "S key pressed" << std::endl;
	}
	if (inputSystem->GetKeyState(SDL_SCANCODE_A))
	{
		playerTransform->Translate(glm::vec3(-0.1f, 0.0f, 0.0f));
		std::cout << "A key pressed" << std::endl;
	}
	if (inputSystem->GetKeyState(SDL_SCANCODE_D))
	{
		playerTransform->Translate(glm::vec3(0.1f, 0.0f, 0.0f));
		std::cout << "D key pressed" << std::endl;
	}

    // Player-specific update logic
    //std::cout << "Ticking Player Component. . ." << m_count << std::endl;
    //m_count++;

    if (m_count >= 10)
    {
        //GetEntity()->Kill();
    }
}