#include "Core.h"
#include "Entity.h"
#include "MeshRenderer.h"
#include "Audio.h"
#include "HUD.h"
#include "SphereCollider.h"

#include <random>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <direct.h>

namespace ECS
{
	struct Player;

	Core::Core()
	{
		// Ensure running starts true and pointers are initialized
		isRunning = true;
		m_window = nullptr;
		m_glcontext = nullptr;
	}
	Core::~Core()
	{

	}


	std::shared_ptr<Core> Core::Initialise()
	{
		//create instance of core - singleton pattern
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		//give weak ptr to itself
		rtn->m_self = rtn;
		return rtn;
	}



	void Core::Start(std::shared_ptr <ECS::Entity> PlayerEntity, std::shared_ptr <ECS::Entity> AudioEntity, std::vector <std::shared_ptr <ECS::Entity> > Walls)
	{
		//initialise window and OpenGL context
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			// Something went very wrong in initialisation, all we can do is exit
			std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
			return;
		}

		// Major version number (4):
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		// Minor version number (3):
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		int winPosX = 100;
		int winPosY = 100;
		int winWidth = 640;
		int winHeight = 640;
		m_window = SDL_CreateWindow("My Window!!!",  // The first parameter is the window title
			winPosX, winPosY,
			winWidth, winHeight,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		SDL_Renderer* renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (!renderer)
		{
			std::cerr << "ERROR: SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return;
		}

		// Now that the SDL renderer is created for the window, we can create an OpenGL context for it!
		// This will allow us to actually use OpenGL to draw to the window
		m_glcontext = SDL_GL_CreateContext(m_window);
		if (!m_glcontext)
		{
			std::cerr << "ERROR: SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return;
		}

		if (!InitGL())
		{
			std::cerr << "ERROR: Unable to initialise OpenGL!" << std::endl;
			SDL_GL_DeleteContext(m_glcontext);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return;
		}
		glEnable(GL_DEPTH_TEST);

		auto meshRenderer = PlayerEntity->GetComponent<MeshRenderer>();
		if (meshRenderer)
		{
			// Diagnostic: print working directory and check presence of files the engine will try to open.
			char cwdBuf[1024];
			if (_getcwd(cwdBuf, sizeof(cwdBuf)))
			{
				std::cout << "INFO: Current working directory: " << cwdBuf << std::endl;
			}
			auto exists = [](const std::string& p) -> bool { std::ifstream f(p); return f.good(); };

			std::vector<std::string> checkPaths = {
				"low-poly-rat/rattri.obj",
				"low-poly-rat/rat_low_lambert1_BaseMap.bmp",
				"vertex.txt",
				"fragment.txt"
			};
			for (const auto& p : checkPaths)
			{
				std::cout << "INFO: Checking file: " << p << " -> " << (exists(p) ? "FOUND" : "MISSING") << std::endl;
			}

			// existing behaviour
			meshRenderer->OnLoadMesh("low-poly-rat/rattri.obj");
			meshRenderer->SetTexturePath("low-poly-rat/rat_low_lambert1_BaseMap.bmp");
			meshRenderer->SetVertexShaderPath("vertex.txt");
			meshRenderer->SetFragmentShaderPath("fragment.txt");
		}
		auto transform = PlayerEntity->GetComponent<Transform>();
		if (transform)
		{
			transform->SetPosition(glm::vec3(4.0f, -1.0f, -10.0f));
		}

		auto audioComp = AudioEntity->GetComponent<Audio>();
		if (audioComp)
		{
			audioComp->InitialiseInstance("BattleIntro.wav");
			audioComp->PlaySound();
		}
		auto playerHud = PlayerEntity->GetComponent<HUD>();
		if (playerHud)
		{
			playerHud->Load_Font();

		}

		for (int i = 0; i < 4; i++)
		{
			auto WallMesh = Walls[i]->GetComponent<MeshRenderer>();
			WallMesh->OnLoadMesh("model_model/model.obj");
			WallMesh->SetTexturePath("model_model/Material__32_albedo.bmp");

			auto WallTransform = Walls[i]->GetComponent<Transform>();
			switch (i)
			{
			case 1:
				WallTransform->SetPosition(glm::vec3(-1.0f, -2.0f, -10.0f));
				break;
			case 2:
				WallTransform->SetPosition(glm::vec3(-1.0f, 2.0f, -10.0f));
				break;
			case 3:
				WallTransform->SetPosition(glm::vec3(-5.0f, -2.0f, -10.0f));
				break;
			case 4:
				WallTransform->SetPosition(glm::vec3(-5.0f, 2.0f, -10.0f));
				break;
			}
		}
		
		// Random generator for when walls respawn
		static std::default_random_engine rng(static_cast<unsigned>(std::random_device{}()));
		// Slight random offset each time walls are repositioned
		std::uniform_real_distribution<float> yOffsetDist(-0.6f, 0.6f);
		const float minY = -3.5f; 
		const float maxY = 3.5f;

		isRunning = true;
		//main game loop
		while (isRunning)
		{

			// Poll for SDL events (keyboard, mouse, window, etc.)
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				m_inputSystem.HandleInput(event);
				m_inputSystem.Update(event);
			}

			//check for quit
			if (m_inputSystem.ShouldQuit())
			{
				Stop();
			}

			// Clear the screen to black
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			

			for (int i = 0; i < 4; i++)
			{
				auto WallTransform = Walls[i]->GetComponent<Transform>();
				auto WallCollider = Walls[i]->GetComponent<SphereCollider>();
				if (WallTransform->GetPosition().x > 8.0f)
				{
					// determine the paired wall index (0&1, 2&3)
					int otherIndex = (i % 2 == 0) ? (i + 1) : (i - 1);

					// compute a small random vertical offset that will be applied to both walls
					float yOffset = yOffsetDist(rng);

					// apply offset to both walls in the pair and clamp within bounds
					auto t0 = Walls[i]->GetComponent<Transform>();
					auto t1 = Walls[otherIndex]->GetComponent<Transform>();

					glm::vec3 pos0 = t0->GetPosition();
					glm::vec3 pos1 = t1->GetPosition();

					pos0.y = std::max(minY, std::min(maxY, pos0.y + yOffset));
					pos1.y = std::max(minY, std::min(maxY, pos1.y + yOffset));

					// reset X for the wall that wrapped and keep the same Z
					// choose reset X based on original design (-1.0f for first column, -5.0f for second)
					float resetX = (i < 2) ? -1.0f : -5.0f;

					t0->SetPosition(glm::vec3(resetX, pos0.y, pos0.z));
					t1->SetPosition(glm::vec3(t1->GetPosition().x, pos1.y, t1->GetPosition().z));

					
					if (i == 1 || i == 3)
					{
						playerHud->score += 1;
					}
					glm::vec3 dir(0.0f);
					if (WallCollider->CollidingAABB(glm::vec3(WallTransform->GetPosition().x - WallCollider->_radius, WallTransform->GetPosition().y, WallTransform->GetPosition().z),
						glm::vec3(WallTransform->GetPosition().x - WallCollider->_radius, WallTransform->GetPosition().y, WallTransform->GetPosition().z), dir, 0.001f))
					{
						std::cout << "Collision Detected" << std::endl;
						std::cout << "Final Score: " << playerHud->score << std::endl;
						Stop();
					}
				}
				else {
					WallTransform->Translate(glm::vec3(0.1f, 0.0f, 0.0f));
				}
			}
			////update entities
			for (Entity* entity : m_entities)
			{
				entity->Update(0.0f); //placeholder deltaTime
				entity->Draw();
			}
			if (playerHud)
			{
				std::stringstream ss;
				ss << "Score: " << playerHud->score;
				playerHud->Render_Text(ss.str(), 25.0f, 25.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
			}
			// Swap the buffers to display the current rendered frame
			SDL_GL_SwapWindow(m_window);
			
		}
	}
	void Core::Stop()
	{
		isRunning = false;
		//cleanup phase
		SDL_GL_DeleteContext(m_glcontext);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}


	std::shared_ptr<Entity> Core::AddEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		rtn->m_core = m_self;
		rtn->m_self = rtn;
		m_entities.push_back(rtn.get());
		return rtn;
	}

	bool Core::InitGL()
	{
		// GLEW has a problem with loading core OpenGL
		// See here: https://www.opengl.org/wiki/OpenGL_Loading_Library
		// The temporary workaround is to enable its 'experimental' features
		glewExperimental = GL_TRUE;

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			std::cerr << "Error: GLEW failed to initialise with message: " << glewGetErrorString(err) << std::endl;
			return false;
		}
		std::cout << "INFO: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

		std::cout << "INFO: OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "INFO: OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "INFO: OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		return true;
	}


}
