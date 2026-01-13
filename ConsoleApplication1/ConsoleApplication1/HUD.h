#pragma once

#include "Component.h"
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <map>
#include <sstream>



namespace ECS
{
	struct HUD : Component
	{
	public:
		void Initialise();
		void DisplayScore();

		SDL_Surface* m_text;
		TTF_Font* font;
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		int score{ 0 };

	};

}