#pragma once

#include <Source/ECS/ECSDefines.h>
#include <Source/Serialisation/Serialiser.h>

using namespace Firelight::Serialisation;

struct HealthComponent : Firelight::ECS::BaseComponent
{
	int currentHealth = 1;
	int startHealth = 1;
	int maxHealth = 1;

	void Serialise() override
	{
		Serialiser::Serialise("CurrentHealth", currentHealth);
		Serialiser::Serialise("StartHealth", startHealth);
		Serialiser::Serialise("MaxHealth", maxHealth);
	}

	HealthComponent* Clone() override
	{
		HealthComponent* clone = new HealthComponent();
		clone->currentHealth = currentHealth;
		clone->startHealth = startHealth;
		clone->maxHealth = maxHealth;
		return clone;
	}
};