#include "Audio.h"

using namespace ECS;

Audio::Audio()
{

}
Audio::~Audio()
{

}

void Audio::InitialiseInstance()
{
	//music (constant)
	int result = Mix_OpenAudio(4410, MIX_DEFAULT_FORMAT, 1, 1024);
	if (result != 0)
	{
		std::cout << "failed to start audio" << std::endl;
	}
	m_music = Mix_LoadMUS("BattleIntro.wav");
	if (!m_music)
	{
		std::cout << "Failed to load music " << Mix_GetError() << std::endl;
	}
}

void Audio::PlaySound(const std::string filePath)
{
	Mix_PlayMusic(m_music, -1);
}

void Audio::StopSound(const std::string filePath)
{
	Mix_HaltMusic();
}

