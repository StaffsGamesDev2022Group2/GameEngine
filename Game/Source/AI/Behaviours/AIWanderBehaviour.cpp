#include "AIWanderBehaviour.h"

AIWanderBehaviour::AIWanderBehaviour(float wanderInterval, float wanderRadius, float speed) : m_WanderInterval(wanderInterval), m_WanderRadius(wanderRadius), m_Speed(speed)
{
	m_CurWanderTime = 0.0f;
}

void AIWanderBehaviour::HandleState(const Firelight::Utils::Time& time)
{
	m_CurWanderTime += time.GetDeltaTime();

	if (m_CurWanderTime > m_WanderInterval)
	{
		m_CurWanderTime = 0.0f;
		float test = 2.0f;
	}
}