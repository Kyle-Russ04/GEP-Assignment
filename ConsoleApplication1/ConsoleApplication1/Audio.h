#pragma once

#include <string>

namespace ECS
{
	struct Audio
	{
		Audio();
		~Audio();

		void Initialise();
		void PlaySound(const char* filePath);

		//data
		std::string m_audioFilePath;
	};
}

