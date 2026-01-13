#include "HUD.h"


using namespace ECS;


void HUD::Initialise()
{
	//initialising the text
	if (TTF_Init() < 0)
	{
		std::cout << "Text initialised failed: " << TTF_GetError() << std::endl;
	}

	font = TTF_OpenFont("Minecraft.ttf", 24);
	if (!font)
	{
		std::cout << "Font failed to initialise" << std::endl;
	}
	SDL_Color colour = { 0,0,0 };
	std::stringstream  Words;
	Words << "Score: " << score;
	m_text = TTF_RenderText_Solid(font, Words.str().c_str(), colour);
	if (!m_text)
	{
		std::cout << "text error" << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(renderer, m_text);
	if (!texture)
	{
		std::cout << "texture error" << std::endl;
	}
}

void HUD::DisplayScore()
{
	SDL_Color colour = { 0,0,0 };
	std::stringstream  Words;
	Words << "Score: " << score;
	m_text = TTF_RenderText_Solid(font, Words.str().c_str(), colour);
	texture = SDL_CreateTextureFromSurface(renderer, m_text);
	SDL_FreeSurface(m_text);
}
