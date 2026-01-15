#pragma once

#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>
#include "Component.h"

namespace ECS
{
	//this is for sound effects
	struct AudioComponent : Component
	{
		void InitialiseInstance();
		void PlaySound(const std::string filePath);
		void StopSound(const std::string filePath);

		//data
		std::string m_audioFilePath;
		Mix_Chunk* m_audio{ nullptr };
	};

}