#pragma once
#include <mc/src/common/world/item/IFoodItemComponent.hpp>
#include <mc/src/common/world/effect/EffectDuration.hpp>
#include <mc/src-deps/core/string/StringHash.hpp>

class FoodItemComponentLegacy : public IFoodItemComponent {
public:
	enum class OnUseAction : int {
		None = -1,
		ChorusTeleport = 0,
		SuspiciousStewEffect = 1
	};

	struct Effect {
		int id;
		std::string name;
		std::string descriptionId;
		EffectDuration duration;
		int amplifier;
		float chance;
	};

public:
	Item& mOwner;
	int mNutrition;
	float mSaturationModifier;
	std::string mUsingConvertsTo;
	FoodItemComponentLegacy::OnUseAction mOnUseAction;
	Vec3 mOnUseRange;
	HashedString mCooldownCategory;
	int mCooldownDuration;
	bool mCanAlwaysEat;
	FoodItemComponentLegacy::Effect mEffects;
	std::vector<unsigned int> mRemoveEffects;
};