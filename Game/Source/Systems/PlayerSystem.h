#pragma once

#include <Source/ECS/Systems/System.h>

#include "../Player/PlayerEntity.h"

class PlayerSystem : public Firelight::ECS::System
{
public:
	PlayerSystem();
	~PlayerSystem();
	void CheckForPlayer();
	void Update(const Firelight::Utils::Time& time) override;

private:
	size_t m_playerEntityAddedCheckIndex;
	PlayerEntity* playerEntity;
};