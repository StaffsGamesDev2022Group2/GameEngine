#pragma once

#include <vector>
#include <memory>

#include "Systems/System.h"

#include "../Utils/Time.h"

namespace Firelight::ECS
{
	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager();

		void PhysicsUpdate(const Utils::Time& time);
		void Update(const Utils::Time& time);
		void LateUpdate(const Utils::Time& time);

		void RegisterEngineSystems();
		
		template<typename SystemType>
		void RegisterGameSystem()
		{
			m_systems.push_back(std::make_unique<SystemType>());
		}

	private:
		std::vector<std::unique_ptr<System>> m_systems;
	};
}
