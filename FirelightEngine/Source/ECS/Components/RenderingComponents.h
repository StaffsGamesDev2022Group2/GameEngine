#pragma once

#include <string>

#include "../ECSDefines.h"

#include "../../Graphics/Data/Texture.h"
#include "../../Graphics/Data/Colour.h"

#include "../../Maths/Rect.h"

namespace Firelight::ECS
{
	/// <summary>
	/// Contains information required to draw a sprite
	/// </summary>
	struct SpriteComponent : BaseComponent
	{
		Firelight::Graphics::Texture*     texture = nullptr;
		int                               layer = 32;

		Maths::Vec2f                      drawOffset = Maths::Vec2f(0.0f, 0.0f);
		Maths::Vec2f                      spriteDimensions = Maths::Vec2f(-1.0f, -1.0f);

		Firelight::Graphics::Colour::RGBA colour = Firelight::Graphics::Colours::sc_white;
		Maths::Rectf                      sourceRect = Maths::Rectf(0.0f, 0.0f, -1.0f, -1.0f);

		std::string Output() override
		{
			return "layer: " + std::to_string(layer)
				+ ", drawOffset: (" + std::to_string(drawOffset.x) + ", " + std::to_string(drawOffset.y)
				+ "), spriteDimensions: (" + std::to_string(spriteDimensions.x) + ", " + std::to_string(spriteDimensions.y)
				+ "), colour: (r=" + std::to_string(colour.GetR()) + ", g=" + std::to_string(colour.GetG()) + ", b=" + std::to_string(colour.GetB()) + ", a=" + std::to_string(colour.GetA()) +
				"), sourceRect: (" + std::to_string(sourceRect.x) + ", " + std::to_string(sourceRect.y) + ", " + std::to_string(sourceRect.w) + ", " + std::to_string(sourceRect.h) + ")";
		}
	};
}
