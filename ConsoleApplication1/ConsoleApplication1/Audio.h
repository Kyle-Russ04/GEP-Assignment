#pragma once

#include <string>

namespace ECS
{
	struct Audio
	{
		Audio();
		~Audio();

		void InitialiseInstance();
		void PlaySound(const std::string filePath);
		void StopSound(const std::string filePath);
		void PauseSound(const std::string filePath);

		//data
		std::string m_audioFilePath;
	};
}

