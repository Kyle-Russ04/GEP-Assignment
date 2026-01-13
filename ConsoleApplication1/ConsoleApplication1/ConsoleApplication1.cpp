// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//code by k.russouw

//includes necessary standard libraries
#include <iostream>
#include <cstdio>
#include <SDL/SDL.h>
// GUI system: https://github.com/ocornut/imgui
// - prevent compile error by building with: WINDOWS_IGNORE_PACKING_MISMATCH
//#include <imgui.h>
//#include <imgui_impl_sdl.h>
//#include <imgui_impl_opengl3.h>


//includes all necessary ECS files
#include "glew.h"
#include "Core.h"
#include "Entity.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Resource.h"
#include "Mesh.h"
#include "Material.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "Player.h"
#include "Transform.h"
#include "SphereCollider.h"
#include "MeshRenderer.h"
#include "Audio.h"
#include "AudioComponent.h"
#include "HUD.h"

int main(int argc, char* argv[])
{
	std::shared_ptr<ECS::Core> core = ECS::Core::Initialise();

	//entity 1 - player
	std::shared_ptr<ECS::Entity> PlayerEntity = core->AddEntity();
    std::shared_ptr<ECS::Component> component = PlayerEntity->AddComponent<ECS::Player>();
	std::shared_ptr<ECS::Component> meshComp = PlayerEntity->AddComponent<ECS::MeshRenderer>();
	std::shared_ptr<ECS::Component> transformComp = PlayerEntity->AddComponent<ECS::Transform>();
	std::shared_ptr<ECS::Component> colliderComp = PlayerEntity->AddComponent<ECS::SphereCollider>();
	std::shared_ptr<ECS::Component> audioComp = PlayerEntity->AddComponent<ECS::AudioComponent>();
	std::shared_ptr<ECS::Component> HUD = PlayerEntity->AddComponent<ECS::HUD>();

	auto meshRenderer = std::dynamic_pointer_cast<ECS::MeshRenderer>(meshComp);

	//entity 2 - background music
	std::shared_ptr<ECS::Entity> AudioEntity = core->AddEntity();
	std::shared_ptr<ECS::Component> audioCompBackground = AudioEntity->AddComponent<ECS::Audio>();


	
	//initialise resources ie. mesh and material
	ECS::ResourceManager resourceManager;

	//start core loop
	core->Start(PlayerEntity, AudioEntity);

	if (core->isRunning == false)
	{
		core->Stop();
	}

    return 0;
}
