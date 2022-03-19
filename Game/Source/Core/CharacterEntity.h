#pragma once

#include <Source/ECS/EntityWrappers/SpriteEntity.h>

#include "../CoreComponents/HealthComponent.h"

class CharacterEntity : public Firelight::ECS::SpriteEntity
{
public:

	CharacterEntity();
	CharacterEntity(Firelight::ECS::EntityID entityID);

	HealthComponent* GetHealthComponent();
	int GetHealth();
	virtual void RemoveHealth(int amount);
	virtual void HealthBelowZero();
};
