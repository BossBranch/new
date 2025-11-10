/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/item/ItemUseMethod.hpp>

class Item;
class ItemStack;
class Actor;
class Level;
class Player;

class IFoodItemComponent {
public:
	/**@vidx {0}*/
	MC virtual ~IFoodItemComponent();

	/**@vidx {1}*/
	MC virtual int getNutrition();

	/**@vidx {2}*/
	MC virtual float getSaturationModifier();

	/**@vidx {3}*/
	MC virtual bool canAlwaysEat();

	/**@vidx {4}*/
	MC virtual Item const* eatItem(ItemStack&, Actor&, Level&);

	/**@vidx {5}*/
	MC virtual void use(bool& result, ItemStack& stack, Player& player);

	/**@vidx {6}*/
	MC virtual void useTimeDepleted(ItemUseMethod&, ItemStack const&, ItemStack&, Player&, Level&);
};