#pragma once
#include <unordered_set>
#include <string>

class UnlockedRecipesClientComponent {
public:
    int mUnlockedCategories;
    int mNewlyUnlockedCategories;
    std::unordered_set<int> mUnlockedItems;
    std::unordered_set<std::string> mUnlockedRecipes;
    std::unordered_set<std::string> mNewlyUnlockedRecipes;
};