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

int main(int argc, char* argv[])
{
	std::shared_ptr<ECS::Core> core = ECS::Core::Initialise();
	std::shared_ptr<ECS::Entity> PlayerEntity = core->AddEntity();
    std::shared_ptr<ECS::Component> component = PlayerEntity->AddComponent<ECS::Player>();
	std::shared_ptr<ECS::Component> meshComp = PlayerEntity->AddComponent<ECS::MeshRenderer>();
	std::shared_ptr<ECS::Component> transformComp = PlayerEntity->AddComponent<ECS::Transform>();
	std::shared_ptr<ECS::Component> colliderComp = PlayerEntity->AddComponent<ECS::SphereCollider>();
	auto meshRenderer = std::dynamic_pointer_cast<ECS::MeshRenderer>(meshComp);
	
	//initialise resources ie. mesh and material
	ECS::ResourceManager resourceManager;
	
	if (meshRenderer)
	{
		meshRenderer->OnLoadMesh("curuthers/curuthers.obj");
	}
	//start core loop
	core->Start();

	if (core->isRunning == false)
	{
		core->Stop();
	}

	//meshComp->Draw();
    return 0;
}
