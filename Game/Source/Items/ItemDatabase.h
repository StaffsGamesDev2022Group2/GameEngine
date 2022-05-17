#pragma once
#include <Source/ECS/EntityWrappers/Entity.h>
#include <Source/ECS/EntityWrappers/Template.h>

#include <string>
#include <unordered_map>

using namespace Firelight::ECS;

class ItemDatabase
{
public:
	static ItemDatabase* Instance();

	void LoadItems(std::string filepath);

	Entity* CreateInstanceOfItem(int itemID);

	// Bad, should probably be optimised in some way
	int GetItemIdFromName(const std::string& name);

private:
	ItemDatabase();
	~ItemDatabase();
	static ItemDatabase* sm_instance;

	std::unordered_map<int, Template*> itemTemplates;
};

