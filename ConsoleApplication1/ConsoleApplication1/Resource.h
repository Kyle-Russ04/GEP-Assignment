#pragma once

#include <string>
#include <memory>


namespace ECS
{

	struct Resource
	{
		friend struct ResourceManager;

	public:
		std::string GetPath() const
		{
			return m_path;
		}

	protected:
		virtual void onLoad();

	private:
		//must be done as friendship is not inherited
		void Load()
		{
			onLoad();
		}

		std::string m_path;
		std::weak_ptr<ResourceManager> m_resourceManager;
	};

}