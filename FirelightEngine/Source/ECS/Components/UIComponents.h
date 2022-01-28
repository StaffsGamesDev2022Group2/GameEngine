#pragma once
#include <string>
#include "../ECSDefines.h"
#include"../Components/BasicComponents.h"
#include"RenderingComponents.h"
#include<vector>

namespace Firelight::ECS
{
	using CallbackFunctionType = std::function< void() >;
	//Docking Settings
	enum class e_AnchorSettings
	{
		Right,
		TopRight,
		BottomRight,
		Left,
		TopLeft,
		BottomLeft,
		Center,
		Top,
		Bottom,
		None

	};

	//Base Widget
	struct UIWidget : BaseComponent
	{

		PixelSpriteComponent* texture = nullptr;
		TransformComponent* transform = nullptr;
		UINT Index =10;
		//Events 
		bool isPressable = true;
		std::vector<CallbackFunctionType> onLeftPressFunctions;
		std::vector<CallbackFunctionType> onRightPressFunctions;
		std::vector<CallbackFunctionType> onMiddlePressFunctions;
		bool isHover =true;
		std::vector<CallbackFunctionType> onHoverFunctions;
		bool isDrag =true;

		//pos data
		e_AnchorSettings anchorSettings = e_AnchorSettings::None;
		Maths::Vec2f offSet = (0, 0, 0);

		//free elments
		Maths::Vec3f defaultPosition= Maths::Vec3f(0,0,0);
		Maths::Vec3f defaultScale = Maths::Vec3f(1, 1, 0);
		Maths::Vec3f currentScale = Maths::Vec3f(1, 1, 0);
	};

	//Visable UI
	struct UI_Child : UIWidget 
	{
		UIWidget* parent;
	};
	//hold all UI
	struct UI_Canvas : UIWidget
	{
		float layer = 32;
	};
	
	//Local ancoring  panel
	struct UI_Panel : UI_Child
	{
	};
	struct UI_Button : UI_Child
	{
		bool isChangeOfTex = true;
		Graphics::Colour::RGBA colour[3] = { Firelight::Graphics::Colours::sc_white ,Firelight::Graphics::Colours::sc_black,Firelight::Graphics::Colours::sc_defaultMetallic};
		std::vector<Maths::Rectf> rectsOfButton;
		char buttionText;

	};
	struct UI_Immage : UI_Child
	{
		
	};
}