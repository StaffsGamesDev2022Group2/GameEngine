#include "SystemManager.h"

#include "Systems/SpriteRenderSystem.h"
#include"Systems/NDCSpriteRenderSystem.h"
#include"Systems/PixelSpriteRenderSystem.h"
#include "Systems/AnimationSystem.h"
#include"Systems/UISystem.h"
#include "../Source/Physics/PhysicsSystem.h"

namespace Firelight::ECS
{
	Firelight::ECS::SystemManager::SystemManager()
	{
	}

	SystemManager::~SystemManager()
	{
	}

	void SystemManager::Update(const Utils::Time& time)
	{
		for (int systemIndex = 0; systemIndex < m_systems.size(); ++systemIndex)
		{
			m_systems[systemIndex]->Update(time);
		}
	}

	void SystemManager::FixedUpdate(const Utils::Time& time)
	{
		for (int systemIndex = 0; systemIndex < m_systems.size(); ++systemIndex)
		{
			m_systems[systemIndex]->FixedUpdate(time);
		}
	}

	void SystemManager::LateUpdate(const Utils::Time& time)
	{
		for (int systemIndex = 0; systemIndex < m_systems.size(); ++systemIndex)
		{
			m_systems[systemIndex]->LateUpdate(time);
		}
	}

	void SystemManager::RegisterEngineSystems()
	{
		m_systems.push_back(std::make_unique<SpriteRenderSystem>());
		m_systems.push_back(std::make_unique<NDCSpriteRenderSystem>());
		m_systems.push_back(std::make_unique<PixelSpriteRenderSystem>());
		m_systems.push_back(std::make_unique<AnimationSystem>());
		m_systems.push_back(std::make_unique<UI::UISystem>());
		m_systems.push_back(std::make_unique<Firelight::Physics::PhysicsSystem>());
	}
}
