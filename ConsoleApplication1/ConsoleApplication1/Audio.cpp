#include "Audio.h"

using namespace ECS;


void Audio::InitialiseInstance(const std::string filepath)
{
	//music (constant)
	int result = Mix_OpenAudio(4410, MIX_DEFAULT_FORMAT, 1, 1024);
	if (result != 0)
	{
		std::cout << "failed to start audio" << std::endl;
	}
	m_music = Mix_LoadMUS(filepath.c_str());
	if (!m_music)
	{
		std::cout << "Failed to load music " << Mix_GetError() << std::endl;
	}
}

void Audio::PlaySound()
{
	Mix_PlayMusic(m_music, -1);
}

void Audio::StopSound()
{
	Mix_HaltMusic();
}

