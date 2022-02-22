#include "PixelSpriteRenderSystem.h"
#include "../Components/BasicComponents.h"
#include "../Components/RenderingComponents.h"

#include "../../Graphics/GraphicsHandler.h"
#include "../../Graphics/SpriteBatch.h"
#include "../../Graphics/GraphicsEvents.h"
#include "../../Graphics/AssetManager.h"

#include "../EntityComponentSystem.h"

#include "../../Events/EventDispatcher.h"

#include"../Source/Engine.h"
namespace Firelight::ECS
{
	PixelSpriteRenderSystem::PixelSpriteRenderSystem()
	{
		AddWhitelistComponent<PixelSpriteComponent>();
		AddWhitelistComponent<TransformComponent>();
		Events::EventDispatcher::SubscribeFunction<Events::Graphics::OnEarlyRender>(std::bind(&PixelSpriteRenderSystem::Render, this));
	}

	PixelSpriteRenderSystem::~PixelSpriteRenderSystem()
	{
	}

	void PixelSpriteRenderSystem::Render()
	{
		for (int entityIndex = 0; entityIndex < m_entities.size(); ++entityIndex)
		{
			auto* transformComponent = m_entities[entityIndex]->GetComponent<TransformComponent>();
			auto* pixelSpriteComponentItem = m_entities[entityIndex]->GetComponent<PixelSpriteComponent>();

			if (!pixelSpriteComponentItem->toDraw) {
				continue;
			}

			Graphics::Texture* texture = pixelSpriteComponentItem->texture;
			if (texture == nullptr)
			{
				texture = Graphics::AssetManager::Instance().GetDefaultTexture();
			}
			
			
			float width = Engine::Instance().GetWindowDimensionsFloat().x * transformComponent->scale.x;
			float Hight = Engine::Instance().GetWindowDimensionsFloat().y * transformComponent->scale.y;
			Maths::Rectf destRect(
				transformComponent->position.x- width * 0.5f,
				transformComponent->position.y- Hight * 0.5f,
				width, Hight);

			Graphics::GraphicsHandler::Instance().GetSpriteBatch()->PixelDraw(destRect, texture, pixelSpriteComponentItem->layer, transformComponent->rotation, pixelSpriteComponentItem->colour, pixelSpriteComponentItem->sourceRect);

		}
	}
}