#include "Component.h"

namespace ECS
{
	Component::Component()
	{
		m_isAlive = true;
	}
	Component::~Component()
	{

	}

	void Component::Initialise()
	{
		OnInitialise();
	}

	void Component::Update(float deltaTime)
	{
		OnUpdate(deltaTime);
	}

	void Component::Draw()
	{
		OnDraw();
	}

	void Component::Kill()
	{
		m_isAlive = false;
		OnKill();
	}

	bool Component::IsAlive()
	{
		return m_isAlive;
	}

	void Component::OnInitialise()
	{
		//does nothing by default
	}

	void Component::OnUpdate(float deltaTime)
	{
		//does nothing by default
	}

	void Component::OnDraw()
	{
		//does nothing by default
	}

	void Component::OnKill()
	{
		std::cout << "Player Component OnKill" << std::endl;
		m_isAlive = false;
		//does nothing by default
	}

}