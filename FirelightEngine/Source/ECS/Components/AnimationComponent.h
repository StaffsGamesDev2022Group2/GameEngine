#pragma once

#include "../ECSDefines.h"
#include "../Source/Animation/Animation.h"
#include "../Source/Graphics/Data/Texture.h"
#include "../Source/Maths/Rect.h"

#include "../../Serialisation/Serialiser.h"

using namespace Firelight::Serialisation;

#include <string>
#include <map>

namespace Firelight::ECS
{
	struct AnimationComponent : BaseComponent
	{
		Firelight::Animation::Animation* currentAnimation = nullptr;
		float currentFrameCount = 0;
		int currentFrameIndex = 0;
		bool playOnStart = true;
		bool shouldPlay = false;
		std::map<std::string, Firelight::Animation::Animation> animations;

		void Serialise() override
		{
			Serialiser::Serialise("CurrentAnimation", currentAnimation);
			Serialiser::Serialise("CurrentFrameCount", currentFrameCount);
			Serialiser::Serialise("CurrentFrameIndex", currentFrameIndex);
			Serialiser::Serialise("PlayOnStart", playOnStart);
			Serialiser::Serialise("ShouldPlay", shouldPlay);

			//Serialise Map
		}

		AnimationComponent* Clone() override
		{
			AnimationComponent* clone = new AnimationComponent();
			clone->currentAnimation = currentAnimation;
			clone->currentFrameCount = currentFrameCount;
			clone->currentFrameIndex = currentFrameIndex;
			clone->playOnStart = playOnStart;
			clone->shouldPlay = shouldPlay;
			clone->animations = animations;

			return clone;
		}
	};
}

