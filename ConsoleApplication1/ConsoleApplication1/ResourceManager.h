#pragma once

#include <map>
#include <string>
#include <memory>


namespace ECS
{
	struct Resource;

	struct ResourceManager
	{
	private:
		//data
		std::map < std::string, std::shared_ptr<Resource> >m_resources;
		std::weak_ptr<ResourceManager> m_self;

		public:
			//functions/methods
			ResourceManager();
			~ResourceManager();

			std::shared_ptr<ResourceManager> Initialise();
			

			//load resource
			template <typename T>
			std::shared_ptr<T> LoadResource(const std::string& resourcePath)
			{
				//check if resource already loaded
				if (m_resources[resourcePath])
				{
					std::shared_ptr<T> oldResource = std::dynamic_pointer_cast<T>(m_resources[resourcePath]);
					if (oldResource)
					{
						return oldResource;
					}
					else
					{
						return nullptr;
					}
				}

				//load new resource
				std::shared_ptr<T> newResource = std::make_shared<T>();
				newResource->m_path = resourcePath;			//set resource path
				newResource->m_resourceManager = m_self;	//set link to manager
				newResource->Load();						//call load function
				m_resources[resourcePath] = newResource;	//store in map

				return newResource;
			}
	};

}