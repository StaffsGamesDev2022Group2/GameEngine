#pragma once

#include <Source/ECS/Components/UIComponents.h>
#include <Source/ECS/EntityWrappers/UIEntity.h>
#include <Source/ECS/EntityWrappers/UIPanel.h>
#include <Source/ECS/Systems/UISystem.h>
#include<Source/Maths/Vec2.h>
#include <string>
#include <vector>

#include"InventoryComponents.h"
#include"Source/Events/EventDispatcher.h"
#include"InventoryEvents.h"

using namespace Firelight;

struct SlotInfo
{	
	int CurrPos = 0;
	ECS::EntityID SlotID= NULL;
	bool IsUsed = false;
};
struct SlotData
{
	SlotInfo* CurrSlot;
	int StackSize = -1;
	std::vector<ECS::EntityID> EntityIDs;
	ECS::EntityID UITexID;
};
class Inventory
{
public:
	Inventory();
	Inventory(std::string Name);
	~Inventory();

	void SetEntityData(ECS::EntityID ID) { IveID = ID; }
	ECS::EntityID GetEntityData() { return IveID; }

	void CreatInventoryNoPannel(Maths::Vec2f size, float slotCount, ECS::EntityID parent, ECS::e_AnchorSettings Anchor, Maths::Vec2f OffSet);
	void CreatInventoryNoPannel(Maths::Vec2f size, Maths::Vec2f rows, ECS::EntityID parent, ECS::e_AnchorSettings Anchor, Maths::Vec2f OffSet);

	//display controlls
	void LoadInventory(std::vector<ECS::UIPanel*> *PannleToUse, bool ToFit);
	void UnloadInventory();

	//item controlls
	bool AddItem(Firelight::ECS::Entity* item);
	bool AddItem(Firelight::ECS::EntityID item);
	bool AddItem(InventoryStoreData* item, bool useSlotPlacement);

	void RemoveItem(Firelight::ECS::Entity* item);
	void RemoveItem(Firelight::ECS::EntityID item);

	bool FindItem(Firelight::ECS::Entity* item);
	bool FindItem(Firelight::ECS::EntityID item);

	bool RemoveItemType(int howMany, int type);
	int GetItemTypeTotal(int type);
	std::vector<ECS::EntityID> GetItemType(int howMany, int type);

	//slot controlls
	void AddSlot();
	void RemoveSlot(SlotData* item);
	SlotInfo* FindSlot(int Number);

	void Place(InventoryStoreData* slotData);


	std::vector <InventoryStoreData*>* GetNullSlotData() { return &NullSlotData; }
	ECS::UIPanel* GetInventorySpace() { return InventorySpace; }
	std::string GetName() { return m_Name; }
	bool GetIsDisplay() { return isDisplay; }
private:



private:

	//pannle created by this 
	ECS::UIPanel* InventorySpace;


	////data to remove
	//std::string m_Name;
	//UINT SlotCount = 0;
	//int RowCount = 0;
	//int ColoumCount = 0;


	//bool isOutput;
	//bool isInput;
	//bool isSwap;

	//bool isDisplay = false;

	//Maths::Vec2i Size;
	//std::vector<std::pair<SlotInfo, SlotData*>> Grid;

	//invetory entity
	ECS::EntityID IveID;

	//slots to remove
	std::vector <InventoryStoreData*> NullSlotData;
};

