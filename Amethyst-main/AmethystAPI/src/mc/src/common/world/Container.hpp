/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include <cstdint>
#include <unordered_set>
#include <deque>
#include <string>
#include <functional>

class ItemStack;
class ContainerContentChangeListener;
class ContainerSizeChangeListener;
class ContainerRemovedListener;

enum class ContainerType : signed char {
    NONE = -9, 
    INVENTORY = -1, 
    CONTAINER, 
    WORKBENCH, 
    FURNACE, 
    ENCHANTMENT, 
    BREWING_STAND, 
    ANVIL, 
    DISPENSER, 
    DROPPER, 
    HOPPER, 
    CAULDRON, 
    MINECART_CHEST, 
    MINECART_HOPPER, 
    HORSE, 
    BEACON, 
    STRUCTURE_EDITOR, 
    TRADE, 
    COMMAND_BLOCK, 
    JUKEBOX, 
    ARMOR, 
    HAND, 
    COMPOUND_CREATOR, 
    ELEMENT_CONSTRUCTOR, 
    MATERIAL_REDUCER, 
    LAB_TABLE, 
    LOOM, 
    LECTERN, 
    GRINDSTONE, 
    BLAST_FURNACE, 
    SMOKER, 
    STONECUTTER, 
    CARTOGRAPHY, 
    HUD, 
    JIGSAW_EDITOR, 
    SMITHING_TABLE, 
    CHEST_BOAT
};

// It's actually TypedRuntimeId<ContainerRuntimeIdTag, unsigned int, 0>
// mojang likes their raw type wrappers lol :p
using ContainerRuntimeId = unsigned int;

class BlockSource;
class CompoundTag;
class Player;
class Vec3;

// This is probably wrong in some way or outdated, from china
enum class ContainerID : unsigned char {
    CONTAINER_ID_NONE = 0xFF,
    CONTAINER_ID_INVENTORY = 0x0,
    CONTAINER_ID_FIRST = 0x1,
    CONTAINER_ID_LAST = 0x64,
    CONTAINER_ID_OFFHAND = 0x77,
    CONTAINER_ID_ARMOR = 0x78,
    CONTAINER_ID_SELECTION_SLOTS = 0x7A,
    CONTAINER_ID_PLAYER_ONLY_UI = 0x7C,
};

class ContainerCloseListener {
public:
    MC virtual void containerClosed(Player& player) = 0;
    MC virtual ~ContainerCloseListener() = default;
};

class ContainerSizeChangeListener {
public:
    MC virtual void containerSizeChanged(int) = 0;
    MC virtual ~ContainerSizeChangeListener() = default;
};

class ContainerContentChangeListener {
public:
    MC virtual void containerContentChanged(int) = 0;
    MC virtual ~ContainerContentChangeListener() = default;
};

/// @vptr {0x4DC0F70}
class Container {
public:
    ContainerType mContainerType;
    ContainerType mGameplayContainerType;
    std::unordered_set<ContainerContentChangeListener*> mContentChangeListeners;
    std::unordered_set<ContainerSizeChangeListener*> mSizeChangeListeners;
    std::unordered_set<ContainerCloseListener*> mCloseListeners;
    std::unordered_set<ContainerRemovedListener*> mRemovedListeners;
    std::deque<std::function<void(Container&, int, const ItemStack&, const ItemStack&)>> mTransactionContextStack;
    std::string mName;
    bool mCustomName;
    ContainerRuntimeId mContainerRuntimeId;

public:
    /// @signature {48 89 5C 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B D9 48 8D 05 ? ? ? ? 48 89 01 88 51}
    MC Container(ContainerType type);
    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 41 0F B6 F1 49 8B F8 48 8B D9 48 8D 05}
    MC Container(ContainerType type, const std::string& containerName, bool hasCustomName);

public:
    /// @vidx {0}
    MC virtual ~Container();
    /// @vidx {1}
    MC virtual void init();
    /// @vidx {2}
    MC virtual void serverInitItemStackIds(int, int, std::function<void(int, const ItemStack&)>) = 0;
    /// @vidx {3}
    MC virtual void addContentChangeListener(ContainerContentChangeListener*);
    /// @vidx {4}
    MC virtual void removeContentChangeListener(ContainerContentChangeListener*);
    /// @vidx {5}
    MC virtual void addRemovedListener(ContainerRemovedListener*);
    /// @vidx {6}
    MC virtual void removeRemovedListener(ContainerRemovedListener*);
    /// @vidx {7}
    MC virtual const ItemStack& getItem(int) const = 0;
    /// @vidx {8}
    MC virtual bool hasRoomForItem(const ItemStack&);
    /// @vidx {9}
    MC virtual void addItem(ItemStack&);
    /// @vidx {10}
    MC virtual void addItemWithForceBalance(ItemStack&);
    /// @vidx {11}
    MC virtual bool addItemToFirstEmptySlot(const ItemStack&);
    /// @vidx {12}
    MC virtual void setItem(int, const ItemStack&) = 0;
    /// @vidx {13}
    MC virtual void setItemWithForceBalance(int, const ItemStack&, bool);
    /// @vidx {14}
    MC virtual void removeItem(int, int);
    /// @vidx {15}
    MC virtual void removeAllItems();
    /// @vidx {16}
    MC virtual void removeAllItemsWithForceBalance();
    /// @vidx {17}
    MC virtual void containerRemoved();
    /// @vidx {18}
    MC virtual void dropSlotContent(BlockSource&, const Vec3&, bool, int);
    /// @vidx {19}
    MC virtual void dropContents(BlockSource&, const Vec3&, bool);
    /// @vidx {20}
    MC virtual int getContainerSize() const = 0;
    /// @vidx {21}
    MC virtual int getMaxStackSize() const = 0;
    /// @vidx {22}
    MC virtual void startOpen(Player&) = 0;
    /// @vidx {23}
    MC virtual void stopOpen(Player&);
    /// @vidx {24}
    MC virtual std::vector<ItemStack> getSlotCopies() const;
    /// @vidx {25}
    MC virtual const std::vector<const ItemStack*> getSlots() const;
    /// @vidx {26}
    MC virtual int getEmptySlotsCount() const;
    /// @vidx {27}
    MC virtual int getItemCount(const ItemStack&);
    /// @vidx {28}
    MC virtual int findFirstSlotForItem(const ItemStack&) const;
    /// @vidx {29}
    MC virtual bool canPushInItem(int, int, const ItemStack&) const;
    /// @vidx {30}
    MC virtual bool canPullOutItem(int, int, const ItemStack&) const;
    /// @vidx {31}
    MC virtual void setContainerChanged(int);
    /// @vidx {32}
    MC virtual void setContainerMoved();
    /// @vidx {33}
    MC virtual void setCustomName(const std::string& name);
    /// @vidx {34}
    MC virtual bool hasCustomName() const;
    /// @vidx {35}
    MC virtual void readAdditionalSaveData(const CompoundTag&);
    /// @vidx {36}
    MC virtual void addAdditionalSaveData(CompoundTag&);
    /// @vidx {37}
    MC virtual void createTransactionContext(std::function<void (Container&, int, ItemStack const&, ItemStack const&)>, std::function<void()>);
    /// @vidx {38}
    MC virtual void initializeContainerContents(BlockSource&);
    /// @vidx {39}
    MC virtual bool isEmpty() const;
    /// @vidx {40}
    MC virtual bool isSlotDisabled(int slot);
};

// 1.21.0.3
static_assert(sizeof(Container) == 352);