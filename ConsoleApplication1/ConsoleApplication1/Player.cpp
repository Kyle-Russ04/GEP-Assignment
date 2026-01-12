#include "Player.h"

using namespace ECS;

void Player::OnUpdate(float deltaTime)
{
    // Player-specific update logic
    //std::cout << "Ticking Player Component. . ." << m_count << std::endl;
    //m_count++;

    if (m_count >= 10)
    {
        //GetEntity()->Kill();
    }
}