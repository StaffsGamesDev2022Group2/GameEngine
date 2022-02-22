#pragma once

#include <Source/ECS/ECSDefines.h>
#include <Source/Serialisation/Serialiser.h>

#include <string>

using namespace Firelight::Serialisation;

struct PlayerComponent : Firelight::ECS::BaseComponent
{
	std::string name = "";
	float speed = 5;

	void Serialise() override
	{
		Serialiser::Serialise("Name", name.c_str());
		Serialiser::Serialise("Speed", speed);
	}

	PlayerComponent* Clone() override
	{
		PlayerComponent* clone = new PlayerComponent();
		clone->name = name;
		clone->speed = speed;
		return clone;
	}
};
