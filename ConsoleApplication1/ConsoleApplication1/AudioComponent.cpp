#include "AudioComponent.h"

using namespace ECS;

AudioComponent::AudioComponent()
{
}

AudioComponent::~AudioComponent()
{
}

void AudioComponent::InitialiseInstance()
{
	//music (constant)
	int result = Mix_OpenAudio(4410, MIX_DEFAULT_FORMAT, 1, 1024);
	if (result != 0)
	{
		std::cout << "failed to start audio" << std::endl;
	}
	m_audio = Mix_LoadWAV("Laser_Shoot.wav");
	if (!m_audio)
	{
		std::cout << "Failed to load music " << Mix_GetError() << std::endl;
	}
}

void AudioComponent::PlaySound(const std::string filePath)
{
	Mix_PlayChannel(-1, m_audio, 0);
}

void AudioComponent::StopSound(const std::string filePath)
{
	Mix_HaltChannel(-1);
}


