#pragma once

#include <string>

#include "../ECSDefines.h"

#include "../../Graphics/Data/Texture.h"
#include "../../Graphics/Data/Colour.h"

#include "../../Maths/Rect.h"

namespace Firelight::ECS
{
	/// <summary>
	/// Contains information about a camera
	/// </summary>
	struct Camera2DComponent : BaseComponent
	{
		float viewportWorldHeight = 20.0f;

		void Serialise() override
		{
			return;
		}
	};

	/// <summary>
	/// Contains information required to draw a sprite
	/// </summary>
	struct SpriteComponent : BaseComponent
	{
		Firelight::Graphics::Texture*     texture = nullptr;
		int                               layer = 32;

		Maths::Vec2f                      drawOffset = Maths::Vec2f(0.0f, 0.0f);
		float                             pixelsPerUnit = 100.0f;

		Firelight::Graphics::Colour::RGBA colour = Firelight::Graphics::Colours::sc_white;
		Maths::Rectf                      sourceRect = Maths::Rectf(0.0f, 0.0f, -1.0f, -1.0f);

		void Serialise() override
		{
			return;
		}
	};


	/// <summary>
	/// Contains information required to draw a NDC sprite
	/// </summary>
	struct NDCSpriteComponent : BaseComponent
	{
		Firelight::Graphics::Texture*     texture = nullptr;
		int                               layer = 32;

		Maths::Vec2f                      drawOffset = Maths::Vec2f(0.0f, 0.0f);

		Firelight::Graphics::Colour::RGBA colour = Firelight::Graphics::Colours::sc_white;
		Maths::Rectf                      sourceRect = Maths::Rectf(0.0f, 0.0f, -1.0f, -1.0f);
		Maths::Rectf                      descRect = Maths::Rectf(0.0f, 0.0f, -1.0f, -1.0f);

		void Serialise() override
		{
			return;
		}
	};

	/// <summary>
	/// Contains information required to draw a Pixle sprite
	/// </summary>
	struct PixleSpriteComponent : BaseComponent
	{
		Firelight::Graphics::Texture* texture = nullptr;
		int                               layer = 32;

		Maths::Vec2f                      drawOffset = Maths::Vec2f(0.0f, 0.0f);

		Firelight::Graphics::Colour::RGBA colour = Firelight::Graphics::Colours::sc_white;
		Maths::Rectf                      sourceRect = Maths::Rectf(0.0f, 0.0f, -1.0f, -1.0f);
		bool    toDraw = true;
		void Serialise() override
		{
			return;
		}
	};
}
