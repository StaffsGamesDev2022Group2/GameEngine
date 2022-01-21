#pragma once

#include "Panel.h"

#include <vector>

namespace Firelight::ECS
{
	class Entity;
}

class InspectorPanel;

class HierarchyPanel : public Panel
{
public:
	HierarchyPanel();

	void Draw() override;
	void NewGameEntity();
	void NewCameraEntity();
	void NewSpriteEntity();
	void DeleteGameEntity(Firelight::ECS::Entity* entity);

private:
	void DrawEntityNode(Firelight::ECS::Entity* entity);

public:
	InspectorPanel* m_inspectorPanel;
	std::vector<Firelight::ECS::Entity*> m_entitiesInScene;
private:
	Firelight::ECS::Entity* m_selectionContext;
};