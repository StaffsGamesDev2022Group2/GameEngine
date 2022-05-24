#include "AIFleeingBehaviour.h"

#include <Source/ECS/Systems/AnimationSystem.h>

AIFleeingBehaviour::AIFleeingBehaviour(EntityID id, RigidBodyComponent* rigidbodyComponent, AIComponent* targetAIComponent, std::string walkAnimation, float speed) :
	m_entityID(id),
	m_rigidBodyComponent(rigidbodyComponent),
	m_targetAIComponent(targetAIComponent),
	m_walkAnimation(walkAnimation),
	m_speed(speed) { }

void AIFleeingBehaviour::HandleState(AIEntity* entity, const Firelight::Utils::Time& time)
{
	if (m_targetAIComponent == nullptr || m_targetAIComponent->m_Target == nullptr)
		return;

	RigidBodyComponent* targetRigidbody = m_targetAIComponent->m_Target->GetComponent<RigidBodyComponent>();
	Firelight::Maths::Vec3f dir = targetRigidbody->nextPos - m_rigidBodyComponent->nextPos;
	dir.Normalise();

	float colliderWidth = 0.0f;
	float colliderHeight = 0.0f;
	if (entity->HasComponent<ColliderComponent, CircleColliderComponent>())
	{
		colliderWidth = entity->GetComponent<ColliderComponent, CircleColliderComponent>()->radius / 2;
		colliderHeight = colliderWidth;
	}
	else if (entity->HasComponent<ColliderComponent, BoxColliderComponent>())
	{
		BoxColliderComponent* boxCollider = entity->GetComponent<ColliderComponent, BoxColliderComponent>();
		colliderWidth = boxCollider->rect.w / 2;
		colliderHeight = boxCollider->rect.h / 2;
	}

	Vec3f targetDir = Vec3f(colliderWidth * dir.x, colliderHeight * dir.y, 0.0f);
	targetDir.Normalise();

	m_rigidBodyComponent->velocity -= targetDir * m_speed * time.GetDeltaTime();
	float magnitude = m_rigidBodyComponent->velocity.Length();
	if (m_walkAnimation != "" && magnitude > 0.05f)
	{
		AnimationSystem::Instance()->Play(entity, m_walkAnimation);
	}
}
