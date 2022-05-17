#include "CraftingRecipeDatabase.h"

#include <fstream>
#include <sstream>

#include "ItemDatabase.h"

CraftingRecipeDatabase::CraftingRecipeDatabase()
{
}

CraftingRecipeDatabase::~CraftingRecipeDatabase()
{
}

CraftingRecipeDatabase& CraftingRecipeDatabase::Instance()
{
	static CraftingRecipeDatabase instance;
	return instance;
}

void CraftingRecipeDatabase::LoadCraftingRecipes(const std::string& filepath)
{
	std::vector<std::vector<std::string>> tableValues;
	std::vector<std::string> row;
	std::string line, value;

	std::fstream csvFile(filepath, std::ios::in);
	if (csvFile.is_open())
	{
		// Skip the first line with the column names
		getline(csvFile, line);

		// Retrieve the actual values
		while (getline(csvFile, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, value, ','))
			{
				row.push_back(value);
			}
			tableValues.push_back(row);
		}
	}

	for (int recipeIndex = 0; recipeIndex < tableValues.size(); ++recipeIndex)
	{
		std::vector<std::string>& recipeValues = tableValues[recipeIndex];

		// Item to make
		std::string itemName = recipeValues[0];
		int itemId = ItemDatabase::Instance()->GetItemIdFromName(itemName);
		
		// Count of item to be made
		int countMaking = std::stoi(recipeValues[1]);

		// Required Items
		std::stringstream requiredItemsSS(recipeValues[2]);
		std::string nameCountString;
		std::vector<CraftingRecipe::ItemRequirement> requiredItems;

		while (getline(requiredItemsSS, nameCountString, '|'))
		{
			std::stringstream nameCountSplitterSS(nameCountString);

			CraftingRecipe::ItemRequirement itemRequirement;

			// Get required item name
			std::string requiredItemString;
			getline(nameCountSplitterSS, requiredItemString, ':');

			itemRequirement.m_itemId = ItemDatabase::Instance()->GetItemIdFromName(requiredItemString);

			// Get required item count
			std::string requiredItemCount;
			getline(nameCountSplitterSS, requiredItemCount, ':');

			itemRequirement.m_numRequired = std::stoi(requiredItemCount);

			// Add it to the list
			requiredItems.push_back(itemRequirement);
		}

		// Actually construct the recipe object
		m_recipes.push_back(new CraftingRecipe(itemId, countMaking, requiredItems));
	}
}
