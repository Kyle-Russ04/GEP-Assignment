#pragma once
#include "Component.h"
#include "InputSystem.h"
#include "Core.h"
#include "Entity.h"
#include <memory>

namespace ECS
{
    struct Player : ECS::Component
    {
    protected:
        void OnUpdate(float deltaTime);

    private:
        int m_count = 0;
        std::unique_ptr<ECS::InputSystem> inputSystem;
    };
}

