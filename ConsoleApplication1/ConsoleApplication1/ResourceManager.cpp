#include "ResourceManager.h"


namespace ECS
{
	ResourceManager::ResourceManager()
	{
	}
	ResourceManager::~ResourceManager()
	{
	}
	std::shared_ptr<ResourceManager> ResourceManager::Initialise()
	{
		std::shared_ptr<ResourceManager> rtn = std::make_shared<ResourceManager>();
		return rtn;
	}
}