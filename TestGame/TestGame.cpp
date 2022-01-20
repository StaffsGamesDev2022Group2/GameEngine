
// Defines the entry point for the application.

#include "Source/Engine.h"
#include "Source/Utils/ErrorManager.h"
#include "Source/ECS/EntityComponentSystem.h"
#include "Source/ECS/Components.h"
#include "Source/ImGuiUI/ImGuiManager.h"

#include "Source/Maths/Vec3.h"
#include "Source/Maths/Vec2.h"
#include "Source/Maths/Rect.h"

#include "ImGuiTestLayer.h"

#include "Source/Graphics/AssetManager.h"
#include "Source/Graphics/Data/Model.h"
#include "Source/Graphics/Data/VertexTypes.h"
#include "Source/Graphics/Data/Colour.h"

#include "Source/Graphics/SpriteBatch.h"

using namespace Firelight;
using namespace Firelight::ECS;
using namespace Firelight::ImGuiUI;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	if (Engine::Instance().Initialise(hInstance, "Test Window", "windowClass", Maths::Vec2i(1280, 720)))
	{
		// ImGui Test code
		ImGuiTestLayer* testLayer = new ImGuiTestLayer();
		ImGuiManager::Instance()->AddRenderLayer(testLayer);
		ImGuiManager::Instance()->RemoveRenderLayer(testLayer);

		Graphics::Model* model = Graphics::AssetManager::Instance().GetModel<Graphics::FancyLitVertex>("cube.obj");

		Graphics::Texture* glowTexture = Graphics::AssetManager::Instance().GetTexture("$ENGINE/Textures/non_binary_transparency.png");
		Graphics::Texture* pepeTexture = Graphics::AssetManager::Instance().GetTexture("$ENGINE/Textures/transparency_test.png");

		const int numPepes = 100;
		struct Pepe
		{
			Maths::Vec2f pos;
			Maths::Vec2f vel;
			float rot = 0.0f;
			float rotSpeed = 0.0f;
			Graphics::Colour colour;
			int layer = 0;
		};
		Pepe pepes[numPepes];

		const auto& windowDimensions = Engine::Instance().GetWindowDimensionsFloat();

		for (int pepeIndex = 0; pepeIndex < numPepes; ++pepeIndex)
		{
			pepes[pepeIndex].vel = Maths::Vec2f::GetRandomVector() * 300.0f;
			pepes[pepeIndex].layer = (int)(Maths::Random::ZeroToOne<float>() * 64.0f);
			pepes[pepeIndex].rotSpeed = Maths::Random::NegOneToOne<float>() * 10.0f;
			BYTE darkness = (BYTE)(255.0f * ((float)pepes[pepeIndex].layer / 64.0f));
			pepes[pepeIndex].colour = Graphics::Colour(darkness, darkness, darkness, 255);
		}

		while (Engine::Instance().ProcessMessages())
		{
			double deltaTime = Engine::Instance().Update();
			for (int pepeIndex = 0; pepeIndex < numPepes; ++pepeIndex)
			{
				Pepe& pepe = pepes[pepeIndex];

				pepe.pos += pepe.vel * (float)deltaTime;
				pepe.rot += pepe.rotSpeed * (float)deltaTime;

				if (pepe.pos.x > windowDimensions.x + 100.0f) pepe.pos.x -= windowDimensions.x + 200.0f;
				if (pepe.pos.x < -100.0f) pepe.pos.x += windowDimensions.x + 200.0f;
				if (pepe.pos.y > windowDimensions.y + 100.0f) pepe.pos.y -= windowDimensions.y + 200.0f;
				if (pepe.pos.y < -100.0f) pepe.pos.y += windowDimensions.y + 200.0f;

				Graphics::GraphicsHandler::Instance().GetSpriteBatch()->PixelDraw(Maths::Rectf(pepe.pos.x - 100.0f, pepe.pos.y - 100.0f, 200.0f, 200.0f), pepeTexture, pepe.layer, (double)pepe.rot, pepe.colour);
			}

			Graphics::GraphicsHandler::Instance().GetSpriteBatch()->PixelDraw(Maths::Rectf(100.0f, 100.0f, 200.0f, 200.0f), Graphics::AssetManager::Instance().GetDefaultTexture(), 64);

			Graphics::GraphicsHandler::Instance().GetSpriteBatch()->PixelDraw(Maths::Rectf(200.0f, 200.0f, 400.0f, 400.0f), glowTexture, 48);
			Graphics::GraphicsHandler::Instance().GetSpriteBatch()->PixelDraw(Maths::Rectf(800.0f, 0.0f, 400.0f, 400.0f), glowTexture, 32);
			Graphics::GraphicsHandler::Instance().GetSpriteBatch()->PixelDraw(Maths::Rectf(400.0f, 300.0f, 400.0f, 400.0f), glowTexture, 16);

			Engine::Instance().RenderFrame();
		}
	}

	return 0;
}
