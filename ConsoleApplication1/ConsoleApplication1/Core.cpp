#include "Core.h"
#include "Entity.h"
#include "MeshRenderer.h"

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



	void Core::Start(std::shared_ptr <ECS::Entity> PlayerEntity)
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
			meshRenderer->OnLoadMesh("low-poly-rat/rattri.obj");
		}

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

			////update entities
			for (Entity* entity : m_entities)
			{
				entity->Update(0.0f); //placeholder deltaTime

				entity->Draw();
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
