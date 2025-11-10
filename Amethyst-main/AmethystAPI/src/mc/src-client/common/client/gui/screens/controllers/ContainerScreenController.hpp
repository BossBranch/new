/// @symbolgeneration
#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <amethyst/Imports.hpp>
#include "mc/src/common/world/containers/ContainerEnumName.hpp"
#include "mc/src-client/common/client/gui/screens/controllers/ClientInstanceScreenController.hpp"

enum class UIProfile;
enum class FadeInIconBehavior;
class ClientInstanceScreenModel;
class ItemStackBase;
class ItemStack; 
class SlotData;
class SelectedSlotInfo;
class ContainerManagerController;
class AutoPlaceItem;
enum class InteractionModel : int {  
    CombinedInventory = 0x0000, 
    SeparateInventoryAndHotbar = 0x0001,
};

struct MojangContainerEnumHasher {
    size_t operator()(ContainerEnumName key) const noexcept
    {
        uint64_t h = 0xCBF29CE484222325ull;
        h ^= static_cast<uint64_t>(key);
        h *= 0x9FFAAC085635BC91ull;
        return static_cast<size_t>(h);
    } 
}; 
 
/// @vptr {0x4CD2850}  
class ContainerScreenController : public ClientInstanceScreenController {
public: 
    // Just to clarify, that doesn't really exist in the binary.
    // It's just here to make it clear. 
    class Lambdas {
    public:
        class ShouldShowItemStackDurability {
        public:
            ContainerScreenController* mScreenController;

            /** @sig {40 53 48 83 EC ? 48 8B 09 48 8B 01 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 48 8B D8 80 78 ? ? 74 ? 48 8B 40 ? 48 85 C0 74 ? 48 83 38 ? 74 ? 48 8B CB E8 ? ? ? ? 84 C0 75 ? 38 43 ? 74 ? 48 8B CB} */
            MC bool operator()(const std::string& collection, int index);
        };
    };

    MC static uintptr_t $vtable_for_this;

    std::byte padding3128[0x1010 - sizeof(ClientInstanceScreenController)];
    std::unordered_map<std::string, std::vector<std::string>> mCoalesceOrderMap;
    std::unordered_map<std::string, std::vector<AutoPlaceItem>> mAutoPlaceOrderMap;
    std::byte padding4240[0xB0];
    InteractionModel mInteractionModel;
    std::shared_ptr<ContainerManagerController> mContainerManagerController;

    /// @address {0x59D9150}
    MC static std::unordered_map<ContainerEnumName, std::string, MojangContainerEnumHasher> ContainerCollectionNameMap;

    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8B F8 48 8B F2}
    MC ContainerScreenController(std::shared_ptr<ClientInstanceScreenModel> model, InteractionModel interactionModel);

    /// @vidx {inherit}
    MC virtual ~ContainerScreenController();
    /// @vidx {inherit}
    MC virtual ui::DirtyFlag tick() override;
    /// @vidx {inherit}
    MC virtual void onOpen() override;
    /// @vidx {inherit}
    MC virtual void onLeave() override;
    /// @vidx {inherit}
    MC virtual ui::DirtyFlag handleGameEventNotification(ui::GameEventNotification) override;
    /// @vidx {inherit}
    MC virtual void setAssociatedBlockPos(const BlockPos&) override;
    /// @vidx {inherit}
    MC virtual void setAssociatedEntityUniqueID(ActorUniqueID) override;
    /// @vidx {inherit}
    MC virtual void addStaticScreenVars(Json::Value&) override;
    /// @vidx {inherit}
    MC virtual bool _isStillValid(void) override;
    /// @vidx {inherit}
    MC virtual bool _getGestureControlEnabled() override;
    /// @vidx {inherit}
    MC virtual std::string _getButtonADescription() override;
    /// @vidx {inherit}
    MC virtual std::string _getButtonXDescription() override;
    /// @vidx {inherit}
    MC virtual std::string _getButtonYDescription() override;
    /// @vidx {53}
    MC virtual void _handleTakeHalf(const std::string&, int);
    /// @vidx {54}
    MC virtual void _handlePlaceAll(const std::string&, int);
    /// @vidx {55}
    MC virtual void _handlePlaceOne(const std::string&, int);
    /// @vidx {56}
    MC virtual void _handleTakePlace(const std::string&, int, bool);
    /// @vidx {57}
    MC virtual void _handleSelectSlot(const std::string&, int);
    /// @vidx {58}
    MC virtual SelectedSlotInfo _getSelectedSlotInfo();
    /// @vidx {59}
    MC virtual void _reevaluateSlotData(SlotData&&);
    /// @vidx {60}
    MC virtual const ItemStack& _getItemStack(const std::string& collection, int index);
    /// @vidx {61}
    MC virtual const ItemStackBase& _getVisualItemStack(const std::string& collection, int index);
    /// @vidx {62}
    MC virtual const ItemStackBase& _getTakeableItemStackBase(const std::string& collection, int index);
    /// @vidx {63}
    MC virtual ui::ViewRequest _onContainerSlotHovered(const std::string& collection, int index);
    /// @vidx {64}
    MC virtual ui::ViewRequest _onContainerSlotUnhovered(const std::string& collection, int index);
    /// @vidx {65}
    MC virtual ui::ViewRequest _onContainerSlotSelected(const std::string& collection, int index);
    /// @vidx {66}
    MC virtual ui::ViewRequest _onContainerSlotPressed(const std::string& collection, int index);
    /// @vidx {67}
    MC virtual bool _shouldSwap(const std::string& collectionLhs, int indexLhs, const std::string& collectionRhs, int indexRhs);
    /// @vidx {68}
    MC virtual bool _isTargetSwappable(const std::string& collection, int index);
    /// @vidx {69}
    MC virtual std::string _getCollectionName(UIPropertyBag*);
    /// @vidx {70} 
    MC virtual bool _canSplit(const std::string&);
    /// @vidx {71}
    MC virtual void _sendFlyingItem(const ItemStackBase&, const std::string&, int, const std::string&, int, FadeInIconBehavior);
    /// @vidx {72}
    MC virtual void _registerCoalesceOrder();
    /// @vidx {73}
    MC virtual void _registerAutoPlaceOrder();
    /// @vidx {74}
    MC virtual void _createItemLockNotification(bool);
    /// @vidx {75}
    MC virtual int _getProgressiveBarDirection(const std::string&, int);
    /// @vidx {76}
    MC virtual void unknown_76();
    /// @vidx {77}
    MC virtual bool _isInCreativeContainer(const std::string&);
     
// Non-virtuals
public:
    static InteractionModel interactionModelFromUIProfile(UIProfile profile);

    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 89 4D ? 0F 57 C0 B9 ? ? ? ? 0F 11 44 24 ? E8 ? ? ? ? 0F 10 05 ? ? ? ? 4C 8B C0 48 89 44 24 ? BF}
    MC void _registerStateMachine();

    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 4C 8B F9}
    MC void _registerEventHandlers();

    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B F9}
    MC void _registerBindings();

    InteractionModel getInteractionModel() const;
};

static_assert(sizeof(ContainerScreenController) == 0x1158);
static_assert(offsetof(ContainerScreenController, mContainerManagerController) == 0x1148);