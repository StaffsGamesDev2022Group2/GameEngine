#pragma once
#include <Source/ECS/ECSDefines.h>
#include <Source/Serialisation/Serialiser.h>

using namespace Firelight::Serialisation;
using namespace Firelight::ECS;

enum class AIType
{
	Passive,
	Neutral,
	Aggresive
};

enum class AIState
{
	Idle,
	Wandering,
	Fleeing,
	Attacking
};

struct AIComponent : Firelight::ECS::BaseComponent
{
public:

	AIType m_Type;
	AIState m_State;

	Entity* m_Target;
	float m_SearchRadius;

public:

	AIComponent* Clone() override
	{
		AIComponent* clone = new AIComponent();
		clone->m_Type = m_Type;
		clone->m_State = m_State;
		clone->m_Target = m_Target;

		return clone;
	}
	
};