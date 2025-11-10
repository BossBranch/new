#if defined(CLIENT) || defined(SERVER)
#include "hooks/shared/ItemRegistry.hpp"

#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>
#include <amethyst/runtime/events/RegisterEvents.hpp>

#include <mc/src/common/world/item/VanillaItems.hpp>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>

void RegisterCreativeItems(ItemRegistryRef ref, CreativeItemCategory category) {
	auto& sharedCtx = Amethyst::GetCurrentThreadCtx();
	auto& vanillaCategory = sharedCtx.mCreativeRegistry.GetVanillaCategory(CreativeItemCategory::Construction);
	vanillaCategory._RegisterItems(ref);
}

namespace Amethyst::SharedHooks::ItemRegistryHooks {
	Amethyst::InlineHook<decltype(&VanillaItems::registerItems)> _VanillaItems_registerItems;
	void VanillaItems_registerItems(
		VanillaItems* self,
		const ItemRegistryRef itemRegistry,
		const BaseGameVersion& baseGameVersion,
		const Experiments& experiments
	) {
		_VanillaItems_registerItems(
			self,
			itemRegistry,
			baseGameVersion,
			experiments
		);

		ItemRegistry* registry = itemRegistry.mItemRegistry.lock().get();
		auto& shared = Amethyst::GetCurrentThreadCtx();
		RegisterItemsEvent event(*registry, shared.mCreativeRegistry);
		Amethyst::GetEventBus().Invoke(event);
	}

	Amethyst::InlineHook<decltype(&VanillaItems::_addItemsCategory)> _VanillaItems__addItemsCategory;
	void VanillaItems__addItemsCategory(
		::CreativeItemRegistry* creative,
		ItemRegistryRef ref,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_VanillaItems__addItemsCategory(creative, ref, version, experiments);
		RegisterCreativeItems(ref, CreativeItemCategory::Items);
	}

	Amethyst::InlineHook<decltype(&VanillaItems::_addCommandOnlyCategory)> _VanillaItems__addCommandOnlyCategory;
	void VanillaItems__addCommandOnlyCategory(
		::CreativeItemRegistry* creative,
		ItemRegistryRef ref,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_VanillaItems__addCommandOnlyCategory(creative, ref, version, experiments);
		RegisterCreativeItems(ref, CreativeItemCategory::ItemCommandOnly);
	}

	Amethyst::InlineHook<decltype(&VanillaItems::_addEquipmentCategory)> _VanillaItems__addEquipmentCategory;
	void VanillaItems__addEquipmentCategory(
		::CreativeItemRegistry* creative,
		ItemRegistryRef ref,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_VanillaItems__addEquipmentCategory(creative, ref, version, experiments);
		RegisterCreativeItems(ref, CreativeItemCategory::Equipment);
	}

	Amethyst::InlineHook<decltype(&VanillaItems::_addNatureCategory)> _VanillaItems__addNatureCategory;
	void VanillaItems__addNatureCategory(
		::CreativeItemRegistry* creative,
		ItemRegistryRef ref,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_VanillaItems__addNatureCategory(creative, ref, version, experiments);
		RegisterCreativeItems(ref, CreativeItemCategory::Nature);
	}

	Amethyst::InlineHook<decltype(&VanillaItems::_addConstructionCategory)> _VanillaItems__addConstructionCategory;
	void VanillaItems__addConstructionCategory(
		::CreativeItemRegistry* creative,
		ItemRegistryRef ref,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_VanillaItems__addConstructionCategory(creative, ref, version, experiments);
		RegisterCreativeItems(ref, CreativeItemCategory::Construction);
	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		HOOK(VanillaItems, registerItems);
		HOOK(VanillaItems, _addItemsCategory);
		HOOK(VanillaItems, _addCommandOnlyCategory);
		HOOK(VanillaItems, _addEquipmentCategory);
		HOOK(VanillaItems, _addNatureCategory);
		HOOK(VanillaItems, _addConstructionCategory);
	}
}
#endif