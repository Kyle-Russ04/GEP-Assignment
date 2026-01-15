#pragma once

#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>
#include "Component.h"

namespace ECS
{
	//this is for background music
	struct Audio : Component
	{
		Audio();
		~Audio();

		void InitialiseInstance(const std::string filepath);
		void PlaySound();
		void StopSound();


		//data
		std::string m_audioFilePath;
		Mix_Music* m_music{ nullptr };
	};
}

