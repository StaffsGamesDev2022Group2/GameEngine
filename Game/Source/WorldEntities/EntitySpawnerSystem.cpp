#include "EntitySpawnerSystem.h"

#include "EntitySpawnerComponent.h"
#include "../Core/ResourceEntity.h"
#include "ResourceDatabase.h"
#include "../AI/Enemies/AICrocodileEntity.h"
#include "../AI/Enemies/AISlimeEntity.h"
#include "../AI/Enemies/AIDeerEntity.h"
#include "../AI/Enemies/AIBunnyEntity.h"
#include "../AI/Enemies/AIBearEntity.h"
#include <Source/ECS/EntityWrappers/SpriteEntityTemplate.h>
#include "../Core/Layers.h"
#include <Source/Graphics/AssetManager.h>
#include <Source/ECS/Components/AnimationComponent.h>
#include "../AI/AIBehaviourComponent.h"

using namespace Firelight::ECS;

EntitySpawnerSystem::EntitySpawnerSystem()
{
	AddWhitelistComponent<EntitySpawnerComponent>();

	SetupEntityTemplate();
}

void EntitySpawnerSystem::Update(const Firelight::Utils::Time& time, const bool& isPaused)
{
	if (isPaused)
	{
		return;
	}

	for (size_t entityIndex = 0; entityIndex < m_entities.size(); ++entityIndex)
	{
		Entity currentEntity = Entity(m_entities[entityIndex]->GetEntityID());
		EntitySpawnerComponent* entitySpawnerComponent = currentEntity.GetComponent<EntitySpawnerComponent>();
		if (entitySpawnerComponent->spawnedEntity != nullptr)
		{
			if (entitySpawnerComponent->spawnedEntity->GetComponent<AIComponent>() != nullptr)
			{
				if (entitySpawnerComponent->spawnedEntity->GetComponent<AIComponent>()->isDead)
				{
					entitySpawnerComponent->spawnedEntity->Destroy();
					entitySpawnerComponent->spawnedEntity = nullptr;
					continue;
				}
			}

			if (entitySpawnerComponent->spawnedEntity->GetComponent<ResourceComponent>() != nullptr)
			{
				if (entitySpawnerComponent->spawnedEntity->GetComponent<ResourceComponent>()->isDead)
				{
					entitySpawnerComponent->spawnedEntity->Destroy();
					entitySpawnerComponent->spawnedEntity = nullptr;
					continue;
				}
			}

			continue;
		}

		entitySpawnerComponent->respawnTimer += time.GetDeltaTime();
		if (entitySpawnerComponent->respawnTimer >= entitySpawnerComponent->respawnCooldown)
		{
			entitySpawnerComponent->respawnTimer = 0.0f;
			
			Firelight::Maths::Vec3f spawnPos = currentEntity.GetComponent<TransformComponent>()->GetPosition();
			if (entitySpawnerComponent->enemyName != "")
			{
				// Spawn new enemy
				if (entitySpawnerComponent->enemyName == "Crocodile")
				{
					AICrocodileEntity* croc = new AICrocodileEntity(true, enemyTemplate->GetTemplateID());
					entitySpawnerComponent->spawnedEntity = croc;
					croc->GetRigidBodyComponent()->interpolate = false;
					croc->GetTransformComponent()->SetPosition(spawnPos);
					croc->GetRigidBodyComponent()->nextPos = spawnPos;
					croc->GetRigidBodyComponent()->interpolate = true;
				}
				else if (entitySpawnerComponent->enemyName == "Slime")
				{
					AISlimeEntity* slime = new AISlimeEntity(true, enemyTemplate->GetTemplateID());
					entitySpawnerComponent->spawnedEntity = slime;
					slime->GetRigidBodyComponent()->interpolate = false;
					slime->GetTransformComponent()->SetPosition(spawnPos);
					slime->GetRigidBodyComponent()->nextPos = spawnPos;
					slime->GetRigidBodyComponent()->interpolate = true;
				}
				else if (entitySpawnerComponent->enemyName == "Deer")
				{
					AIDeerEntity* deer = new AIDeerEntity(true, enemyTemplate->GetTemplateID());
					entitySpawnerComponent->spawnedEntity = deer;
					deer->GetRigidBodyComponent()->interpolate = false;
					deer->GetTransformComponent()->SetPosition(spawnPos);
					deer->GetRigidBodyComponent()->nextPos = spawnPos;
					deer->GetRigidBodyComponent()->interpolate = true;
				}
				else if (entitySpawnerComponent->enemyName == "Bunny")
				{
					AIBunnyEntity* bunny = new AIBunnyEntity(true, enemyTemplate->GetTemplateID());
					entitySpawnerComponent->spawnedEntity = bunny;
					bunny->GetRigidBodyComponent()->nextPos = spawnPos;
				}
				else if (entitySpawnerComponent->enemyName == "Bear")
				{
					AIBearEntity* bear= new AIBearEntity(true, enemyTemplate->GetTemplateID());
					entitySpawnerComponent->spawnedEntity = bear;
					bear->GetRigidBodyComponent()->nextPos = spawnPos;
				}
			}
			else if (entitySpawnerComponent->resourceID != -1)
			{
				// Spawn new resource
				ResourceEntity* resourceEntity = ResourceDatabase::Instance()->CreateInstanceOfResource(entitySpawnerComponent->resourceID);
				entitySpawnerComponent->spawnedEntity = resourceEntity;
				resourceEntity->GetRigidBodyComponent()->interpolate = false;
				resourceEntity->GetTransformComponent()->SetPosition(spawnPos);
				resourceEntity->GetRigidBodyComponent()->nextPos = spawnPos;
				resourceEntity->GetRigidBodyComponent()->interpolate = true;
			}
		}
	}
}

void EntitySpawnerSystem::SetupEntityTemplate()
{
	enemyTemplate = new SpriteEntityTemplate("Enemy Template");
	AIComponent* aiComponent = enemyTemplate->AddComponent<AIComponent>();
	enemyTemplate->GetComponent<LayerComponent>()->layer = static_cast<int>(GameLayer::Enemy);
	SpriteComponent* spriteComponent = enemyTemplate->GetComponent<SpriteComponent>();
	spriteComponent->texture = Firelight::Graphics::AssetManager::Instance().GetTexture("Sprites/Enemies/DeerIdle.png");
	spriteComponent->pixelsPerUnit = 50;
	spriteComponent->layer = static_cast<int>(RenderLayer::Enemy);
	enemyTemplate->AddComponent<RigidBodyComponent>();
	enemyTemplate->AddComponent<AIBehaviourComponent>();
	enemyTemplate->AddComponent<HealthComponent>();
	enemyTemplate->AddComponent<Firelight::ECS::AnimationComponent>();
	AudioComponent* audioComponent = new AudioComponent();
	enemyTemplate->AddComponent<Firelight::ECS::AudioComponent>(audioComponent);
	audioComponent->looping = false;
	audioComponent->is3d = false;
	audioComponent->streaming = false;
	audioComponent->channel = "Enemies";
}
