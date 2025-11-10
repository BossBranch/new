/// @symbolgeneration
#pragma once
#include <memory>
#include "mc/src/common/world/actor/Mob.hpp"
#include <mc/src/common/world/item/ItemGroup.hpp>
#include <mc/src/common/world/inventory/transaction/InventoryTransactionManager.hpp>
#include <mc/src/common/world/actor/player/SerializedSkin.hpp>
#include <mc/src/common/world/actor/player/PlayerInventory.hpp>
#include <mc/src/common/world/actor/player/SkinAdjustments.hpp>
#include <mc/src/common/world/level/levelgen/structure/StructureFeatureType.hpp>

class ChunkSource;
class ItemStackNetManagerBase;
class PlayerEventCoordinator;
class InventoryTransaction;
class ComplexInventoryTransaction;
class LayeredAbilities;
class IContainerManager;
class GameMode;
class ServerPlayer;
class LocalPlayer;
class UserEntityIdentifierComponent;
class PlayerListener;

class FrameUpdateContextBase;
class ChalkboardBlockActor;
class INpcDialogueData;
class TextObjectRoot;
class ResolvedTextObject;

namespace Editor {
	class IEditorPlayer;
};

enum class BedSleepingResult : int32_t {
	OK = 0x0000,
	NOT_POSSIBLE_HERE = 0x0001,
	NOT_POSSIBLE_NOW = 0x0002,
	TOO_FAR_AWAY = 0x0003,
	OTHER_PROBLEM = 0x0004,
	NOT_SAFE = 0x0005,
	BED_OBSTRUCTED = 0x0006,
};

#pragma pack(push, 8)
/// @vptr {0x4DBEEB8}
class Player : public Mob {
public:
	struct PlayerSpawnPoint {
		BlockPos mSpawnBlockPos;
		BlockPos mPlayerPosition;
		DimensionType mDimension;
	};

    /* this + 1512 */ std::byte padding1512[360];
    /* this + 1872 */ std::shared_ptr<IContainerManager> mContainerManager;
    /* this + 1888 */ PlayerInventory* playerInventory;
    /* this + 1896 */ std::byte padding1896[1920 - 1896];
    /* this + 1920 */ SerializedSkin mSkin;
    /* this + 2528 */ std::byte padding2528[3288 - 2528];
    /* this + 3288 */ ItemGroup mCursorSelectedItemGroup;
    ///* this + 3432 */ PlayerUIContainer mPlayerUIContainer;
    /* this + 3432 */ std::byte padding3432[3736 - 3432];
    /* this + 3736 */ InventoryTransactionManager mTransactionManager;
    /* this + 3784 */ std::unique_ptr<GameMode> mGameMode;
    /* this + 3792 */ std::byte padding3792[2680];
    /* this + 6472 */ std::unique_ptr<ItemStackNetManagerBase> mItemStackNetManager;
    std::shared_ptr<AnimationComponent> mUIAnimationComponent;
	std::shared_ptr<AnimationComponent> mMapAnimationComponent;
	Player::PlayerSpawnPoint mPlayerRespawnPoint;
	SubClientId mClientId;
	float mServerBuildRatio;
	bool mUseMapAnimationComponent;
	bool mIsDeferredRenderingFirstPersonObjects;
	std::shared_ptr<AnimationComponent> mFirstPersonAnimationComponent;
	std::vector<PlayerListener*> mListeners;
	int mLastLevelUpTime;
	bool mPlayerLevelChanged;
	int mPreviousLevelRequirement;
	Vec3 mRespawnPositionCandidate;
	Vec3 mEnterBedPosition;
	Vec3 mPreDimensionTransferSpawnPosition;
	bool mDestroyingBlock;
	std::vector<uint32_t> mOnScreenAnimationTextures;
	int mOnScreenAnimationTicks;
	int mEnchantmentSeed;
	uint32_t mChunkRadius;
	int mMapIndex;
	uint64_t mElytraLoop;
	float mElytraVolume;
	std::unordered_map<HashedString,int> mCooldowns;
	std::unordered_map<HashedString,HashedString> mVanillaCooldowns;
	int64_t mStartedBlockingTimeStamp;
	int64_t mBlockedUsingShieldTimeStamp;
	int64_t mBlockedUsingDamagedShieldTimeStamp;
	bool mPrevBlockedUsingShield;
	bool mPrevBlockedUsingDamagedShield;
	bool mUsedPotion;
	SkinAdjustments mSkinAdjustments;
	SerializedSkin mSerializedSkin;
	std::string mName;
	std::string mLastEmotePlayed;
	int64_t mEmoteEasterEggEndTime;
	uint32_t mEmoteMessageCount;
	std::string mDeviceId;
	bool mFlagClientForBAIReset;
	bool mSendInventoryOptionsToClient;
	bool mIsHostingPlayer;
	bool mOverrideShouldCrit;

    // 101% accurate parameters lmao
    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 44 89 4C 24 ? 4C 89 44 24}
    MC static void $constructor(Player* self, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10, void* a11, void* a12, void* a13, void* a14);

    MC static uintptr_t $vtable_for_this;

    /// @vidx {i}
	MC virtual void reloadHardcoded(ActorInitializationMethod unk0, const VariantParameterList& unk1) override;

	/// @vidx {i}
	MC virtual void initializeComponents(ActorInitializationMethod unk0, const VariantParameterList& unk1) override;

	/// @vidx {i}
	MC virtual void _serverInitItemStackIds() override;

	/// @vidx {i}
	MC virtual ~Player();

	/// @vidx {i}
	MC virtual void resetUserPos(bool unk0) override;

	/// @vidx {i}
	MC virtual void remove() override;

	/// @vidx {i}
	MC virtual Vec3 getInterpolatedRidingOffset(float unk0, int unk1) const override;

	/// @vidx {i}
	MC virtual bool isFireImmune() const override;

	/// @vidx {i}
	MC virtual void teleportTo(const Vec3& unk0, bool unk1, int unk2, int unk3, bool unk4) override;

	/// @vidx {i}
	MC virtual std::unique_ptr<AddActorBasePacket> tryCreateAddActorPacket() override;

	/// @vidx {i}
	MC virtual void normalTick() override;

	/// @vidx {i}
	MC virtual void passengerTick() override;

	/// @vidx {i}
	MC virtual mce::Color getNameTagTextColor() const override;

	/// @vidx {i}
	MC virtual float getShadowRadius() const override;

	/// @vidx {i}
	MC virtual bool canInteractWithOtherEntitiesInGame() const override;

	/// @vidx {i}
	MC virtual bool isImmobile() const override;

	/// @vidx {i}
	MC virtual bool isSilentObserver() const override;

	/// @vidx {i}
	MC virtual bool isSleeping() const override;

	/// @vidx {i}
	MC virtual void setSleeping(bool unk0) override;

	/// @vidx {i}
	MC virtual bool isBlocking() const override;

	/// @vidx {i}
	MC virtual bool isDamageBlocked(const ActorDamageSource& unk0) const override;

	/// @vidx {i}
	MC virtual bool attack(Actor& unk0, const ActorDamageCause& unk1) override;

	/// @vidx {i}
	MC virtual bool isInvulnerableTo(const ActorDamageSource& unk0) const override;

	/// @vidx {i}
	MC virtual void feed(int unk0) override;

	/// @vidx {i}
	MC virtual void handleEntityEvent(ActorEvent unk0, int unk1) override;

	/// @vidx {i}
	MC virtual const HashedString& getActorRendererId() const override;

	/// @vidx {i}
	MC virtual void setArmor(ArmorSlot unk0, const ItemStack& unk1) override;

	/// @vidx {i}
	MC virtual void setCarriedItem(const ItemStack& unk0) override;

	/// @vidx {i}
	MC virtual const ItemStack& getCarriedItem() const override;

	/// @vidx {i}
	MC virtual void setOffhandSlot(const ItemStack& unk0) override;

	/// @vidx {i}
	MC virtual const ItemStack& getEquippedTotem() const override;

	/// @vidx {i}
	MC virtual bool consumeTotem() override;

	/// @vidx {i}
	MC virtual bool canFreeze() const override;

	/// @vidx {i}
	MC virtual bool canChangeDimensionsUsingPortal() const override;

	/// @vidx {i}
	MC virtual float causeFallDamageToActor(float unk0, float unk1, ActorDamageSource unk2) override;

	/// @vidx {i}
	MC virtual void onSynchedDataUpdate(int unk0) override;

	/// @vidx {i}
	MC virtual bool canAddPassenger(Actor& unk0) const override;

	/// @vidx {i}
	MC virtual bool canBePulledIntoVehicle() const override;

	/// @vidx {i}
	MC virtual void sendMotionPacketIfNeeded(const PlayerMovementSettings& unk0) override;

	/// @vidx {i}
	MC virtual void startSwimming() override;

	/// @vidx {i}
	MC virtual void stopSwimming() override;

	/// @vidx {i}
	MC virtual CommandPermissionLevel getCommandPermissionLevel() const override;

	/// @vidx {i}
	MC virtual bool canObstructSpawningAndBlockPlacement() const override;

	/// @vidx {i}
	MC virtual AnimationComponent& getAnimationComponent() override;

	/// @vidx {i}
	MC virtual void useItem(ItemStackBase& unk0, ItemUseMethod unk1, bool unk2) override;

	/// @vidx {i}
	MC virtual float getMapDecorationRotation() const override;

	/// @vidx {i}
	MC virtual bool add(ItemStack& unk0) override;

	/// @vidx {i}
	MC virtual bool drop(const ItemStack& unk0, bool unk1) override;

	/// @vidx {i}
	MC virtual void startSpinAttack() override;

	/// @vidx {i}
	MC virtual void stopSpinAttack() override;

	/// @vidx {i}
	MC virtual void die(const ActorDamageSource& unk0) override;

	/// @vidx {i}
	MC virtual bool shouldDropDeathLoot() const override;

	/// @vidx {i}
	MC virtual std::optional<BlockPos> getLastDeathPos() const override;

	/// @vidx {i}
	MC virtual std::optional<AutomaticID<Dimension, int>> getLastDeathDimension() const override;

	/// @vidx {i}
	MC virtual bool hasDiedBefore() const override;

	/// @vidx {i}
	MC virtual void doEnterWaterSplashEffect() override;

	/// @vidx {i}
	MC virtual void doExitWaterSplashEffect() override;

	/// @vidx {i}
	MC virtual bool _shouldProvideFeedbackOnHandContainerItemSet(HandSlot unk0, const ItemStack& unk1) const override;

	/// @vidx {i}
	MC virtual bool _shouldProvideFeedbackOnArmorSet(ArmorSlot unk0, const ItemStack& unk1) const override;

	/// @vidx {i}
	MC virtual bool _hurt(const ActorDamageSource& unk0, float unk1, bool unk2, bool unk3) override;

	/// @vidx {i}
	MC virtual void readAdditionalSaveData(const CompoundTag& unk0, DataLoadHelper& unk1) override;

	/// @vidx {i}
	MC virtual void addAdditionalSaveData(CompoundTag& unk0) const override;

	/// @vidx {i}
	MC virtual float getSpeed() const override;

	/// @vidx {i}
	MC virtual void setSpeed(float unk0) override;

	/// @vidx {i}
	MC virtual void aiStep() override;

	/// @vidx {i}
	MC virtual int getItemUseDuration() const override;

	/// @vidx {i}
	MC virtual float getItemUseStartupProgress() const override;

	/// @vidx {i}
	MC virtual float getItemUseIntervalProgress() const override;

	/// @vidx {i}
	MC virtual std::vector<const ItemStack*> getAllHand() const override;

	/// @vidx {i}
	MC virtual std::vector<const ItemStack*> getAllEquipment() const override;

	/// @vidx {i}
	MC virtual void dropEquipmentOnDeath(const ActorDamageSource& unk0) override;

	/// @vidx {i}
	MC virtual void dropEquipmentOnDeath() override;

	/// @vidx {i}
	MC virtual void clearVanishEnchantedItemsOnDeath() override;

	/// @vidx {i}
	MC virtual void sendInventory(bool unk0) override;

	/// @vidx {i}
	MC virtual bool canExistWhenDisallowMob() const override;

	/// @vidx {i}
	MC virtual std::unique_ptr<BodyControl> initBodyControl() override;

	/// @vidx {190}
	MC virtual void prepareRegion(ChunkSource& unk0);

	/// @vidx {191}
	MC virtual void destroyRegion();

	/// @vidx {192}
	MC virtual void suspendRegion();

	/// @vidx {193}
	MC virtual void _fireDimensionChanged();

	/// @vidx {194}
	MC virtual void changeDimensionWithCredits(AutomaticID<Dimension, int> unk0);

	/// @vidx {195}
	MC virtual void tickWorld(const Tick& unk0);

	/// @vidx {196}
	MC virtual void frameUpdate(FrameUpdateContextBase& unk0) = 0;

	/// @vidx {197}
	MC virtual const std::vector<ChunkPos>& getTickingOffsets() const;

	/// @vidx {198}
	MC virtual void moveView();

	/// @vidx {199}
	MC virtual void moveSpawnView(const Vec3& unk0, AutomaticID<Dimension, int> unk1);

	/// @vidx {200}
	MC virtual void checkMovementStats(const Vec3& unk0);

	/// @vidx {201}
	MC virtual StructureFeatureType getCurrentStructureFeature() const;

	/// @vidx {202}
	MC virtual bool isAutoJumpEnabled() const;

	/// @vidx {203}
	MC virtual void respawn();

	/// @vidx {204}
	MC virtual void resetRot();

	/// @vidx {205}
	MC virtual bool isInTrialMode();

	/// @vidx {206}
	MC virtual void openPortfolio();

	/// @vidx {207}
	MC virtual void openBook(int unk0, bool unk1, int unk2, BlockActor* unk3);

	/// @vidx {208}
	MC virtual void openTrading(const ActorUniqueID& unk0, bool unk1);

	/// @vidx {209}
	MC virtual void openChalkboard(ChalkboardBlockActor& unk0, bool unk1);

	/// @vidx {210}
	MC virtual void openNpcInteractScreen(std::shared_ptr<INpcDialogueData> unk0);

	/// @vidx {211}
	MC virtual void openInventory();

	/// @vidx {212}
	MC virtual void displayChatMessage(const std::string& unk0, const std::string& unk1);

	/// @vidx {213}
	MC virtual void displayClientMessage(const std::string& unk0);

	/// @vidx {214}
	MC virtual void displayTextObjectMessage(const TextObjectRoot& unk0, const std::string& unk1, const std::string& unk2);

	/// @vidx {215}
	MC virtual void displayTextObjectWhisperMessage(const ResolvedTextObject& unk0, const std::string& unk1, const std::string& unk2);

	/// @vidx {216}
	MC virtual void displayTextObjectWhisperMessage(const std::string& unk0, const std::string& unk1, const std::string& unk2);

	/// @vidx {217}
	MC virtual void displayWhisperMessage(const std::string& unk0, const std::string& unk1, const std::string& unk2, const std::string& unk3);

	/// @vidx {218}
	MC virtual BedSleepingResult startSleepInBed(const BlockPos& unk0);

	/// @vidx {219}
	MC virtual void stopSleepInBed(bool unk0, bool unk1);

	/// @vidx {220}
	MC virtual bool canStartSleepInBed();

	/// @vidx {221}
	MC virtual void openSign(const BlockPos& unk0, bool unk1);

	/// @vidx {222}
	MC virtual void playEmote(const std::string& unk0, bool unk1);

	/// @vidx {223}
	MC virtual bool isLoading() const;

	/// @vidx {224}
	MC virtual bool isPlayerInitialized() const;

	/// @vidx {225}
	MC virtual void stopLoading();

	/// @vidx {226}
	MC virtual void setPlayerGameType(GameType unk0);

	/// @vidx {227}
	MC virtual void initHUDContainerManager();

	/// @vidx {228}
	MC virtual void _crit(Actor& unk0);

	/// @vidx {229}
	MC virtual IMinecraftEventing* getEventing() const;

	/// @vidx {230}
	MC virtual unsigned int getUserId() const;

	/// @vidx {231}
	MC virtual void addExperience(int unk0);

	/// @vidx {232}
	MC virtual void addLevels(int unk0);

	/// @vidx {233}
	MC virtual void setContainerData(IContainerManager& unk0, int unk1, int unk2) = 0;

	/// @vidx {234}
	MC virtual void slotChanged(IContainerManager& unk0, Container& unk1, int unk2, const ItemStack& unk3, const ItemStack& unk4, bool unk5) = 0;

	/// @vidx {235}
	MC virtual void refreshContainer(IContainerManager& unk0) = 0;

	/// @vidx {236}
	MC virtual void deleteContainerManager();

	/// @vidx {237}
	MC virtual bool isActorRelevant(const Actor& unk0);

	/// @vidx {238}
	MC virtual bool isTeacher() const = 0;

	/// @vidx {239}
	MC virtual void onSuspension();

	/// @vidx {240}
	MC virtual void onLinkedSlotsChanged();

	/// @vidx {241}
	MC virtual void sendInventoryTransaction(const InventoryTransaction& unk0) const = 0;

	/// @vidx {242}
	MC virtual void sendComplexInventoryTransaction(std::unique_ptr<ComplexInventoryTransaction> unk0) const = 0;

	/// @vidx {243}
	MC virtual void sendNetworkPacket(Packet& unk0) const;

	/// @vidx {244}
	MC virtual PlayerEventCoordinator& getPlayerEventCoordinator() = 0;

	/// @vidx {245}
	MC virtual bool isSimulated() const;

	/// @vidx {246}
	MC virtual std::string getXuid() const;

	/// @vidx {247}
	MC virtual const PlayerMovementSettings& getMovementSettings() const;

	/// @vidx {248}
	MC virtual void requestMissingSubChunk(const SubChunkPos& unk0);

	/// @vidx {249}
	MC virtual unsigned char getMaxChunkBuildRadius() const;

	/// @vidx {250}
	MC virtual void onMovePlayerPacketNormal(const Vec3& unk0, const Vec2& unk1, float unk2);

	/// @vidx {251}
	MC virtual std::shared_ptr<ChunkViewSource> _createChunkSource(ChunkSource& unk0);

	/// @vidx {252}
	MC virtual void setAbilities(const LayeredAbilities& unk0);

	/// @vidx {253}
	MC virtual Bedrock::NonOwnerPointer<Editor::IEditorPlayer> getEditorPlayer() const = 0;

	/// @vidx {254}
	MC virtual void destroyEditorPlayer() = 0;

    const PlayerInventory& getSupplies() const;
    PlayerInventory& getSupplies();
    const ItemStack& getSelectedItem() const;
    void setSelectedItem(const ItemStack& item);

    // non virtuals
    const LayeredAbilities& getAbilities() const;
    GameMode& getGameMode() const;
    bool canUseOperatorBlocks() const;
    void updateSkin(const SerializedSkin& skin, int clientSubID);

    void setContainerManagerModel(std::shared_ptr<IContainerManager> manager);
    std::weak_ptr<IContainerManager> getContainerManagerModel() const;

    const ServerPlayer* getServerPlayer() const;
    const LocalPlayer* getLocalPlayer() const;
    ServerPlayer* getServerPlayer();
    LocalPlayer* getLocalPlayer();

    SerializedSkin& getSkin();
    const SerializedSkin& getSkin() const;

	const UserEntityIdentifierComponent* getUserIdentity() const;
	UserEntityIdentifierComponent* getUserIdentity();
};
#pragma pack(pop)   


// 1.21.0.3
//static_assert(offsetof(Player, mItemStackNetManager) == 6472);
static_assert(offsetof(Player, playerInventory) == 1888);
//static_assert(offsetof(Player, mTransactionManager) == 3736);
//static_assert(sizeof(Player) == 7592);  


// idk version
//static_assert(offsetof(Player, mPlayerUIContainer) == 3432); 