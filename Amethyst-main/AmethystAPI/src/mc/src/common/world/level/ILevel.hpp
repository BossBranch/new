/// @symbolgeneration
#pragma once
#include <gsl/gsl>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <mc/src-deps/core/utility/AutomaticID.hpp>
#include <mc/src-deps/gamerefs/WeakRef.hpp>
#include <mc/src-deps/core/file/Path.hpp>
#include <mc/src/common/world/level/ChunkPos.hpp>
#include <mc/src/common/world/level/Tick.hpp>
#include <mc/src/common/world/level/storage/StorageVersion.hpp>
#include <mc/src/common/world/level/block/LevelEvent.hpp>
#include <mc/src-deps/gamerefs/OwnerPtr.hpp>
#include <mc/src/common/world/phys/Vec3.hpp>
#include <mc/src-deps/shared_types/legacy/LevelSoundEvent.hpp>
#include <mc/src/common/world/level/GameType.hpp>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <mc/src-client/common/client/social/MultiplayerGameinfo.hpp>
#include <mc/src/common/world/Difficulty.hpp>
#include <mc/src-deps/core/threading/TaskGroup.hpp>
#include <amethyst/Imports.hpp>

// Auto-generated: Forward declarations
namespace PlayerCapabilities { struct ISharedController; }
namespace PositionTrackingDB { class PositionTrackingDBClient; }
namespace cg { class ImageBuffer; }
namespace mce {class UUID; class Color; }
class EntityContext;
class ActorFactory;
struct ActorUniqueID;
class LevelSettings;
class LevelData;
class Experiments;
class ChunkTickRangeManager;
class PortalForcer;
class Player;
class Actor;
class Spawner;
class ProjectileFactory;
class ActorDefinitionGroup;
class BlockDefinitionGroup;
class PropertyGroupManager;
class AutomationBehaviorTreeGroup;
class BehaviorFactory;
class InternalComponentRegistry;
class BlockSource;
class LevelChunk;
class Mob;
class IMinecraftEventing;
class BiomeManager;
class LevelListener;
class ActorDamageSource;
class Explosion;
class BlockPos;
class NavigationComponent;
class PhotoStorage;
class TickingAreasManager;
struct ActorDefinitionIdentifier;
class IConstBlockSource;
class PlayerEventCoordinator;
class ServerPlayerEventCoordinator;
class ClientPlayerEventCoordinator;
class ActorEventCoordinator;
class BlockEventCoordinator;
class ItemEventCoordinator;
class ServerNetworkEventCoordinator;
class ScriptingEventCoordinator;
class ScriptDeferredEventCoordinator;
class LevelEventCoordinator;
class CompoundTag;
class UserEntityIdentifierComponent;
class Block;
struct Bounds;
class ChunkSource;
class NetworkIdentifier;
class _TickPtr;
class Particle;
class HashedString;
class MolangVariableMap;
struct ResolvedItemIconInfo;
class SavedDataStorage;
class MapItemSavedData;
class ActorInfoRegistry;
class EntitySystems;
class TagRegistry;
struct PlayerMovementSettings;
class SerializedSkin;
class PacketSender;
class HitResult;
struct AdventureSettings;
class GameRules;
class Abilities;
class PermissionsHandler;
struct ScreenshotOptions;
class LootTables;
class LayeredAbilities;
class Recipes;
class BlockReducer;
class ItemComponentPacket;
class BlockLegacy;
class Level;
class ChangeDimensionRequest;
class BossEventSubscriptionManager;
class ActorAnimationGroup;
class ActorAnimationControllerGroup;
class DimensionConversionData;
class StrictEntityContext;
class ActorRuntimeID;
class StructureManager;
class Path;
class PlayerSleepStatus;
class EducationLevelSettings;
class ActorEvent;
class IUnknownBlockTypeRegistry;
class NetEventCallback;
class LevelSoundManager;
class SoundPlayerInterface;
class BlockTypeRegistry;
class ChunkViewSource;
class WeakEntityRef;
class Dimension;
class TickingAreaList;
enum class ParticleType : int {};
class BlockPalette;

class ILevel : public Bedrock::EnableNonOwnerReferences {
public:
    /**@vidx {0}*/
    MC virtual ~ILevel();

    /**@vidx {1}*/
    MC virtual bool initialize(const std::string&, const LevelSettings&, LevelData*, const Experiments&, const std::string*);

    /**@vidx {2}*/
    MC virtual void startLeaveGame();

    /**@vidx {3}*/
    MC virtual bool isLeaveGameDone();

    /**@vidx {4}*/
    MC virtual WeakRef<Dimension> getOrCreateDimension(DimensionType);

    /**@vidx {5}*/
    MC virtual WeakRef<Dimension> getDimension(DimensionType) const;

    /**
    * @vidx {6}
    * @brief Validates that the DimensionType != Undefined, in that case resets it to the Overworld
    */
    MC virtual DimensionType getLastOrDefaultSpawnDimensionId(DimensionType) const;

    /**@vidx {7}*/
    MC virtual void _unknown_7();

    /**@vidx {8}*/
    MC virtual void _unknown_8();

    /**@vidx {9}*/
    MC virtual void _unknown_9();

    /**@vidx {10}*/
    MC virtual void _unknown_10();

    /**@vidx {11}*/
    MC virtual unsigned int getChunkTickRange() const;

    /**@vidx {12}*/
    MC virtual const ChunkTickRangeManager& getChunkTickRangeManager() const;

    /**@vidx {13}*/
    MC virtual PortalForcer& getPortalForcer();

    /**@vidx {14}*/
    MC virtual void requestPlayerChangeDimension(Player&, ChangeDimensionRequest&&);

    /**@vidx {15}*/
    MC virtual void entityChangeDimension(Actor&, DimensionType, std::optional<Vec3>);

    /**@vidx {16}*/
    MC virtual Spawner& getSpawner() const;

    /**@vidx {17}*/
    MC virtual gsl::not_null<Bedrock::NonOwnerPointer<BossEventSubscriptionManager>> getBossEventSubscriptionManager();

    /**@vidx {18}*/
    MC virtual ProjectileFactory& getProjectileFactory() const;

    /**@vidx {19}*/
    MC virtual ActorDefinitionGroup* getEntityDefinitions() const;

    /**@vidx {20}*/
    MC virtual gsl::not_null<Bedrock::NonOwnerPointer<ActorAnimationGroup>> getActorAnimationGroup() const;

    /**@vidx {21}*/
    MC virtual Bedrock::NonOwnerPointer<ActorAnimationControllerGroup> getActorAnimationControllerGroup() const;

    /**@vidx {22}*/
    MC virtual BlockDefinitionGroup* getBlockDefinitions() const;

    /**@vidx {23}*/
    MC virtual void _unknown_23();

    /**@vidx {24}*/
    MC virtual void _unknown_24();

    /**@vidx {25}*/
    MC virtual PropertyGroupManager& getActorPropertyGroup() const;

    /**@vidx {26}*/
    MC virtual void _unknown_26();

    /**@vidx {27}*/
    MC virtual void _unknown_27();

    /**@vidx {28}*/
    MC virtual bool getDisablePlayerInteractions() const;

    /**@vidx {29}*/
    MC virtual void setDisablePlayerInteractions(bool);

    /**@vidx {30}*/
    MC virtual AutomationBehaviorTreeGroup& getAutomationBehaviorTreeGroup() const;

    /**@vidx {31}*/
    MC virtual BehaviorFactory& getBehaviorFactory() const;

    /**@vidx {32}*/
    MC virtual Difficulty getDifficulty() const;

    /**@vidx {33}*/
    MC virtual InternalComponentRegistry& getInternalComponentRegistry() const;

    /**@vidx {34}*/
    MC virtual DimensionConversionData getDimensionConversionData() const;

    /**@vidx {35}*/
    MC virtual float getSpecialMultiplier(DimensionType) const;

    /**@vidx {36}*/
    MC virtual bool hasCommandsEnabled() const;

    /**@vidx {37}*/
    MC virtual bool useMsaGamertagsOnly() const;

    /**@vidx {38}*/
    MC virtual void setMsaGamertagsOnly(bool);

    /**@vidx {39}*/
    MC virtual Actor* addEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vidx {40}*/
    MC virtual Actor* addGlobalEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vidx {41}*/
    MC virtual Actor* addAutonomousEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vidx {42}*/
    MC virtual void addUser(OwnerPtr<EntityContext>);

    /**@vidx {43}*/
    MC virtual Actor* addDisplayEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vidx {44}*/
    MC virtual void removeDisplayEntity(WeakEntityRef);

    /**@vidx {45}*/
    MC virtual void suspendPlayer(Player&);

    /**@vidx {46}*/
    MC virtual void resumePlayer(Player&);

    /**@vidx {47}*/
    MC virtual bool isPlayerSuspended(Player&) const;

    /**@vidx {48}*/
    MC virtual OwnerPtr<EntityContext> removeActorAndTakeEntity(WeakEntityRef);

    /**@vidx {49}*/
    MC virtual OwnerPtr<EntityContext> removeActorFromWorldAndTakeEntity(WeakEntityRef);

    /**@vidx {50}*/
    MC virtual OwnerPtr<EntityContext> takeEntity(WeakEntityRef, LevelChunk&);

    /**@vidx {51}*/
    MC virtual StrictEntityContext fetchStrictEntity(ActorUniqueID, bool) const;

    /**@vidx {52}*/
    MC virtual Actor* fetchEntity(ActorUniqueID uniqueId, bool getRemoved) const;

    /**@vidx {53}*/
    MC virtual Actor* getRuntimeEntity(ActorRuntimeID, bool) const;

    /**@vidx {54}*/
    MC virtual Mob* getMob(ActorUniqueID) const;

    /**@vidx {55}*/
    MC virtual Player* getPlayer(const std::string&) const;

    /**@vidx {56}*/
    MC virtual Player* getPlayer(const mce::UUID&) const;

    /**@vidx {57}*/
    MC virtual Player* getPlayer(ActorUniqueID) const;

    /**@vidx {58}*/
    MC virtual Player* getPlayerByXuid(const std::string&) const;

    /**@vidx {59}*/
    MC virtual Player* getPlatformPlayer(const std::string&) const;

    /**@vidx {60}*/
    MC virtual Player* getPlayerFromServerId(const std::string&) const;

    /**@vidx {61}*/
    MC virtual Player* getRuntimePlayer(ActorRuntimeID) const;

    /**@vidx {62}*/
    MC virtual int getNumRemotePlayers();

    /// @vidx {63}
    /// Returns the primary local player (DOES NOT WORK FROM SERVER LEVEL)
    MC virtual Player* getPrimaryLocalPlayer() const;

    /**@vidx {64}*/
    MC virtual IMinecraftEventing& getEventing();

    /**@vidx {65}*/
    MC virtual mce::Color getPlayerColor(const Player&) const;

    /**@vidx {66}*/
    MC virtual const Tick& getCurrentTick() const;

    /**@vidx {67}*/
    MC virtual const Tick getCurrentServerTick() const;

    /**@vidx {68}*/
    MC virtual void _unknown_68();

    /**@vidx {69}*/
    MC virtual void _unknown_69();

    /**@vidx {70}*/
    MC virtual BlockPalette& getBlockPalette() const;

    /**@vidx {71}*/
    MC virtual void _unknown_71();

    /**@vidx {72}*/
    MC virtual void _unknown_72();

    /**@vidx {73}*/
    MC virtual void _unknown_73();

    /**@vidx {74}*/
    MC virtual void _unknown_74();

    /**@vidx {75}*/
    MC virtual void _unknown_75();

    /**@vidx {76}*/
    MC virtual void _unknown_76();

    /**@vidx {77}*/
    MC virtual void _unknown_77();

    /**@vidx {78}*/
    MC virtual gsl::not_null<Bedrock::NonOwnerPointer<StructureManager>> getStructureManager();

    /**@vidx {79}*/
    MC virtual const gsl::not_null<Bedrock::NonOwnerPointer<StructureManager>> getStructureManager() const;

    /**@vidx {80}*/
    MC virtual void _unknown_80();

    /**@vidx {81}*/
    MC virtual void _unknown_81();

    /**@vidx {82}*/
    MC virtual void _unknown_82();

    /**@vidx {83}*/
    MC virtual void _unknown_83();

    /**@vidx {84}*/
    MC virtual BiomeManager& getBiomeManager();

    /**@vidx {85}*/
    MC virtual const BiomeManager& getBiomeManager() const;

    /**@vidx {86}*/
    MC virtual void _unknown_86();

    /**@vidx {87}*/
    MC virtual void _unknown_87();

    /**@vidx {88}*/
    MC virtual void _unknown_88();

    /**@vidx {89}*/
    MC virtual void _unknown_89();

    /**@vidx {90}*/
    MC virtual void _unknown_90();

    /**@vidx {91}*/
    MC virtual void _unknown_91();

    /**@vidx {92}*/
    MC virtual void addListener(LevelListener&);

    /**@vidx {93}*/
    MC virtual void removeListener(LevelListener&);

    /**@vidx {94}*/
    MC virtual void tickEntities();

    /**@vidx {95}*/
    MC virtual void tickEntitySystems();

    /**@vidx {96}*/
    MC virtual void _unknown_96();

    /**@vidx {97}*/
    MC virtual void _unknown_97();

    /**@vidx {98}*/
    MC virtual void onPlayerDeath(Player&, const ActorDamageSource&);

    /**@vidx {99}*/
    MC virtual void tick();

    /**@vidx {100}*/
    MC virtual bool explode(Explosion&);

    /**@vidx {101}*/
    MC virtual bool explode(BlockSource&, Actor*, const Vec3&, float, bool, bool, float, bool);

    /**@vidx {102}*/
    MC virtual void spawnParticleEffect(const std::string&, const Vec3&, Dimension*);

    /**@vidx {103}*/
    MC virtual void denyEffect(BlockSource&, const Vec3&);

    /**@vidx {104}*/
    MC virtual void potionSplash(const Vec3&, const mce::Color&, bool);

    /**@vidx {105}*/
    MC virtual bool extinguishFire(BlockSource&, const BlockPos&, unsigned char, Actor*);

    /**@vidx {106}*/
    MC virtual std::unique_ptr<Path> findPath(Actor&, Actor&, NavigationComponent&);

    /**@vidx {107}*/
    MC virtual std::unique_ptr<Path> findPath(Actor&, int, int, int, NavigationComponent&);

    /**@vidx {108}*/
    MC virtual void updateSleepingPlayerList();

    /**@vidx {109}*/
    MC virtual void setSleepStatus(const PlayerSleepStatus&);

    /**@vidx {110}*/
    MC virtual PlayerSleepStatus getSleepStatus() const;

    /**@vidx {111}*/
    MC virtual int getTime() const;

    /**@vidx {112}*/
    MC virtual void setTime(int);

    /**@vidx {113}*/
    MC virtual unsigned int getSeed();

    /**@vidx {114}*/
    MC virtual const BlockPos& getDefaultSpawn() const;

    /**@vidx {115}*/
    MC virtual void setDefaultSpawn(const BlockPos&);

    /**@vidx {116}*/
    MC virtual void _unknown_116();

    /**@vidx {117}*/
    MC virtual void setDefaultGameType(GameType);

    /**@vidx {118}*/
    MC virtual GameType getDefaultGameType() const;

    /**@vidx {119}*/
    MC virtual void setDifficulty(Difficulty);

    /**@vidx {120}*/
    MC virtual void setMultiplayerGameIntent(bool);

    /**@vidx {121}*/
    MC virtual bool getMultiplayerGameIntent() const;

    /**@vidx {122}*/
    MC virtual void setMultiplayerGame(bool);

    /**@vidx {123}*/
    MC virtual bool isMultiplayerGame() const;

    /**@vidx {124}*/
    MC virtual void setLANBroadcastIntent(bool);

    /**@vidx {125}*/
    MC virtual bool getLANBroadcastIntent() const;

    /**@vidx {126}*/
    MC virtual void setLANBroadcast(bool);

    /**@vidx {127}*/
    MC virtual bool getLANBroadcast() const;

    /**@vidx {128}*/
    MC virtual void setXBLBroadcastIntent(Social::GamePublishSetting);

    /**@vidx {129}*/
    MC virtual Social::GamePublishSetting getXBLBroadcastIntent() const;

    /**@vidx {130}*/
    MC virtual bool hasXBLBroadcastIntent() const;

    /**@vidx {131}*/
    MC virtual void setXBLBroadcastMode(Social::GamePublishSetting);

    /**@vidx {132}*/
    MC virtual Social::GamePublishSetting getXBLBroadcastMode() const;

    /**@vidx {133}*/
    MC virtual bool hasXBLBroadcast() const;

    /**@vidx {134}*/
    MC virtual void setPlatformBroadcastIntent(Social::GamePublishSetting);

    /**@vidx {135}*/
    MC virtual Social::GamePublishSetting getPlatformBroadcastIntent() const;

    /**@vidx {136}*/
    MC virtual bool hasPlatformBroadcastIntent() const;

    /**@vidx {137}*/
    MC virtual void setPlatformBroadcastMode(Social::GamePublishSetting);

    /**@vidx {138}*/
    MC virtual Social::GamePublishSetting getPlatformBroadcastMode() const;

    /**@vidx {139}*/
    MC virtual bool hasPlatformBroadcast() const;

    /**@vidx {140}*/
    MC virtual void setHasLockedBehaviorPack(bool);

    /**@vidx {141}*/
    MC virtual void setHasLockedResourcePack(bool);

    /**@vidx {142}*/
    MC virtual void setCommandsEnabled(bool);

    /**@vidx {143}*/
    MC virtual void setWorldTemplateOptionsUnlocked();

    /**@vidx {144}*/
    MC virtual bool hasLevelStorage() const;

    /**@vidx {145}*/
    MC virtual void _unknown_145();

    /**@vidx {146}*/
    MC virtual void _unknown_146();

    /**@vidx {147}*/
    MC virtual LevelData& getLevelData();

    /**@vidx {148}*/
    MC virtual const LevelData& getLevelData() const;

    /**@vidx {149}*/
    MC virtual PhotoStorage& getPhotoStorage();

    /**@vidx {150}*/
    MC virtual void createPhotoStorage();

    /**@vidx {151}*/
    MC virtual void setEducationLevelSettings(EducationLevelSettings);

    /**@vidx {152}*/
    MC virtual const std::optional<EducationLevelSettings>& getEducationLevelSettings() const;

    /**@vidx {153}*/
    MC virtual void save();

    /**@vidx {154}*/
    MC virtual void saveLevelData();

    /**@vidx {155}*/
    MC virtual void saveGameData();

    /**@vidx {156}*/
    MC virtual std::shared_ptr<void*> requestTimedStorageDeferment();

    /**@vidx {157}*/
    MC virtual TickingAreasManager& getTickingAreasMgr();

    /**@vidx {158}*/
    MC virtual void addTickingAreaList(DimensionType, const std::shared_ptr<TickingAreaList>&);

    /**@vidx {159}*/
    MC virtual void sendServerLegacyParticle(ParticleType, const Vec3&, const Vec3&, int);

    /**@vidx {160}*/
    MC virtual void playSound(DimensionType, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vidx {161}*/
    MC virtual void playSound(const IConstBlockSource&, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vidx {162}*/
    MC virtual void playSound(const std::string&, const Vec3&, float, float);

    /**@vidx {163}*/
    MC virtual void playSound(Puv::Legacy::LevelSoundEvent, const Vec3&, float, float);

    /**@vidx {164}*/
    MC virtual void playSound(Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vidx {165}*/
    MC virtual PlayerEventCoordinator& getRemotePlayerEventCoordinator();

    /**@vidx {166}*/
    MC virtual ServerPlayerEventCoordinator& getServerPlayerEventCoordinator();

    /**@vidx {167}*/
    MC virtual ClientPlayerEventCoordinator& getClientPlayerEventCoordinator();

    /**@vidx {168}*/
    MC virtual ActorEventCoordinator& getActorEventCoordinator();

    /**@vidx {169}*/
    MC virtual BlockEventCoordinator& getBlockEventCoordinator();

    /**@vidx {170}*/
    MC virtual ItemEventCoordinator& getItemEventCoordinator();

    /**@vidx {171}*/
    MC virtual ServerNetworkEventCoordinator& getServerNetworkEventCoordinator();

    /**@vidx {172}*/
    MC virtual ScriptingEventCoordinator& getScriptingEventCoordinator();

    /**@vidx {173}*/
    MC virtual ScriptDeferredEventCoordinator& getScriptDeferredEventCoordinator();

    /**@vidx {174}*/
    MC virtual LevelEventCoordinator& getLevelEventCoordinator();

    /**@vidx {175}*/
    MC virtual void handleLevelEvent(LevelEvent, const CompoundTag&);

    /**@vidx {176}*/
    MC virtual void handleLevelEvent(LevelEvent, const Vec3&, int);

    /**@vidx {177}*/
    MC virtual void handleStopSoundEvent(const std::string&);

    /**@vidx {178}*/
    MC virtual void handleStopAllSounds();

    /**@vidx {179}*/
    MC virtual void broadcastLevelEvent(LevelEvent, const CompoundTag&, const UserEntityIdentifierComponent*);

    /**@vidx {180}*/
    MC virtual void broadcastLevelEvent(LevelEvent, const Vec3&, int, const UserEntityIdentifierComponent*);

    /**@vidx {181}*/
    MC virtual void broadcastLocalEvent(BlockSource&, LevelEvent, const Vec3&, const Block&);

    /**@vidx {182}*/
    MC virtual void broadcastLocalEvent(BlockSource&, LevelEvent, const Vec3&, int);

    /**@vidx {183}*/
    MC virtual void broadcastSoundEvent(Dimension&, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vidx {184}*/
    MC virtual void broadcastSoundEvent(BlockSource&, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vidx {185}*/
    MC virtual void broadcastSoundEvent(BlockSource&, Puv::Legacy::LevelSoundEvent, const Vec3&, const Block&, const ActorDefinitionIdentifier&, bool, bool);

    /**@vidx {186}*/
    MC virtual void broadcastActorEvent(Actor&, ActorEvent, int) const;

    /**@vidx {187}*/
    MC virtual void addChunkViewTracker(std::weak_ptr<ChunkViewSource>);

    /**@vidx {188}*/
    MC virtual void onChunkReload(const Bounds&);

    /**@vidx {189}*/
    MC virtual void onChunkReloaded(ChunkSource&, LevelChunk&);

    /**@vidx {190}*/
    MC virtual int getActivePlayerCount() const;

    /**@vidx {191}*/
    MC virtual int getActiveUsersCount() const;

    /**@vidx {192}*/
    MC virtual void forEachPlayer(std::function<bool(Player&)>);

    /**@vidx {193}*/
    MC virtual void forEachPlayer(std::function<bool(const Player&)>) const;

    /**@vidx {194}*/
    MC virtual void forEachUser(std::function<bool(const EntityContext&)>) const;

    /**@vidx {195}*/
    MC virtual void forEachUser(std::function<bool(EntityContext&)>);

    /**@vidx {196}*/
    MC virtual Player* findPlayer(std::function<bool(const WeakEntityRef&)>) const;

    /**@vidx {197}*/
    MC virtual Player* findPlayer(std::function<bool(const Player&)>) const;

    /**@vidx {198}*/
    MC virtual int getUserCount() const;

    /**@vidx {199}*/
    MC virtual int countUsersWithMatchingNetworkId(const NetworkIdentifier&) const;

    /**@vidx {200}*/
    MC virtual const std::vector<OwnerPtr<EntityContext>>& getUsers() const;

    /**@vidx {201}*/
    MC virtual const std::vector<OwnerPtr<EntityContext>>& getEntities() const;

    /**@vidx {202}*/
    MC virtual void _unknown_202();

    /**@vidx {203}*/
    MC virtual void onChunkLoaded(ChunkSource&, LevelChunk&);

    /**@vidx {204}*/
    MC virtual void onChunkDiscarded(LevelChunk&);

    /**@vidx {205}*/
    MC virtual void _unknown_205();

    /**@vidx {206}*/
    MC virtual void queueEntityDestruction(OwnerPtr<EntityContext>);

    /**@vidx {207}*/
    MC virtual OwnerPtr<EntityContext> removeEntity(WeakEntityRef);

    /**@vidx {208}*/
    MC virtual OwnerPtr<EntityContext> removeEntity(Actor&);

    /**@vidx {209}*/
    MC virtual void forceRemoveEntity(Actor&);

    /**@vidx {210}*/
    MC virtual void forceRemoveEntityfromWorld(Actor&);

    /**@vidx {211}*/
    MC virtual void forceFlushRemovedPlayers();

    /**@vidx {212}*/
    MC virtual void _unknown_212();

    /**@vidx {213}*/
    MC virtual void levelCleanupQueueEntityRemoval(OwnerPtr<EntityContext>);

    /**@vidx {214}*/
    MC virtual void registerTemporaryPointer(_TickPtr&);

    /**@vidx {215}*/
    MC virtual void unregisterTemporaryPointer(_TickPtr&);

    /**@vidx {216}*/
    MC virtual bool destroyBlock(BlockSource& region, const BlockPos& pos, bool dropResources);

    /**@vidx {217}*/
    MC virtual void upgradeStorageVersion(StorageVersion);

    /**@vidx {218}*/
    MC virtual void suspendAndSave();

    /**@vidx {219}*/
    MC virtual Particle* addParticle(ParticleType, const Vec3&, const Vec3&, int, const CompoundTag*, bool);

    /**@vidx {220}*/
    MC virtual void _destroyEffect(const BlockPos&, const Block&, int);

    /**@vidx {221}*/
    MC virtual void addParticleEffect(const HashedString&, const Vec3&, const MolangVariableMap&);

    /**@vidx {222}*/
    MC virtual void addTerrainParticleEffect(const BlockPos&, const Block&, const Vec3&, float, float, float);

    /**@vidx {223}*/
    MC virtual void addTerrainSlideEffect(const BlockPos&, const Block&, const Vec3&, float, float, float);

    /**@vidx {224}*/
    MC virtual void addBreakingItemParticleEffect(const Vec3&, ParticleType, const ResolvedItemIconInfo&);

    /**@vidx {225}*/
    MC virtual ActorUniqueID getNewUniqueID();

    /**@vidx {226}*/
    MC virtual ActorRuntimeID getNextRuntimeID();

    /**@vidx {227}*/
    MC virtual const std::vector<ChunkPos>& getTickingOffsets() const;

    /**@vidx {228}*/
    MC virtual const std::vector<ChunkPos>& getClientTickingOffsets() const;

    /**@vidx {229}*/
    MC virtual std::vector<ChunkPos> getSortedPositionsFromClientOffsets(const std::vector<ChunkPos>&) const;

    /**@vidx {230}*/
    MC virtual bool isExporting() const;

    /**@vidx {231}*/
    MC virtual void setIsExporting(bool);

    /**@vidx {232}*/
    MC virtual SavedDataStorage& getSavedData();

    /**@vidx {233}*/
    MC virtual void _unknown_233();

    /**@vidx {234}*/
    MC virtual void _unknown_234();

    /**@vidx {235}*/
    MC virtual MapItemSavedData* getMapSavedData(ActorUniqueID);

    /**@vidx {236}*/
    MC virtual void requestMapInfo(ActorUniqueID, bool);

    /**@vidx {237}*/
    MC virtual ActorUniqueID expandMapByID(ActorUniqueID, bool);

    /**@vidx {238}*/
    MC virtual bool copyAndLockMap(ActorUniqueID, ActorUniqueID);

    /**@vidx {239}*/
    MC virtual MapItemSavedData& createMapSavedData(const std::vector<ActorUniqueID>&, const BlockPos&, DimensionType, int);

    /**@vidx {240}*/
    MC virtual MapItemSavedData& createMapSavedData(const ActorUniqueID&, const BlockPos&, DimensionType, int);

    /**@vidx {241}*/
    MC virtual Core::PathBuffer<std::string> getScreenshotsFolder() const;

    /**@vidx {242}*/
    MC virtual std::string getLevelId() const;

    /**@vidx {243}*/
    MC virtual void setLevelId(std::string);

    /**@vidx {244}*/
    MC virtual TaskGroup& getSyncTasksGroup();

    /**@vidx {245}*/
    MC virtual TaskGroup& getIOTasksGroup();

    /**@vidx {246}*/
    MC virtual void _unknown_246();

    /**@vidx {247}*/
    MC virtual void _unknown_247();

    /**@vidx {248}*/
    MC virtual void _unknown_248();

    /**@vidx {249}*/
    MC virtual void _unknown_249();

    /**@vidx {250}*/
    MC virtual void _unknown_250();

    /**@vidx {251}*/
    MC virtual bool isEdu() const;

    /// @vidx {253}
	MC virtual ActorFactory& getActorFactory();

	/// @vidx {252}
	MC virtual const ActorFactory& getActorFactory() const;

    /**@vidx {254}*/
    MC virtual ActorInfoRegistry* getActorInfoRegistry();

    /**@vidx {255}*/
    //MC virtual StackRefResult<const EntityRegistry> getEntityRegistry() const;
    MC virtual void _unknown_255();

    /**@vidx {256}*/
    //MC virtual StackRefResult<EntityRegistry> getEntityRegistry();
    MC virtual void _unknown_256();

    /**@vidx {257}*/
    MC virtual EntitySystems& getEntitySystems();

    /**@vidx {258}*/
    MC virtual WeakRef<EntityContext> getLevelEntity();

    /**@vidx {259}*/
    MC virtual void _unknown_259();

    /**@vidx {260}*/
    MC virtual void _unknown_260();

    /**@vidx {261}*/
    MC virtual const PlayerCapabilities::ISharedController& getCapabilities() const;

    /**@vidx {262}*/
    //MC virtual TagRegistry<IDType<LevelTagIDType>, IDType<LevelTagSetIDType>>& getTagRegistry();
    MC virtual void _unknown_262();

    /**@vidx {263}*/
    MC virtual const PlayerMovementSettings& getPlayerMovementSettings() const;

    /**@vidx {264}*/
    MC virtual void setPlayerMovementSettings(const PlayerMovementSettings&);

    /**@vidx {265}*/
    MC virtual bool canUseSkin(const SerializedSkin&, const NetworkIdentifier&, const mce::UUID&, const ActorUniqueID&) const;

    /**@vidx {266}*/
    MC virtual PositionTrackingDB::PositionTrackingDBClient* getPositionTrackerDBClient() const;

    /**@vidx {267}*/
    MC virtual void _unknown_267();

    /**@vidx {268}*/
    MC virtual void flushRunTimeLighting();

    /**@vidx {269}*/
    MC virtual void loadBlockDefinitionGroup(const Experiments&);

    /**@vidx {270}*/
    MC virtual void initializeBlockDefinitionGroup();

    /**@vidx {271}*/
    MC virtual Bedrock::NonOwnerPointer<IUnknownBlockTypeRegistry> getUnknownBlockTypeRegistry();

    /**@vidx {272}*/
    MC virtual bool isClientSide() const;

    /**@vidx {273}*/
    MC virtual void _unknown_273();

    /**@vidx {274}*/
    MC virtual void _unknown_274();

    /**@vidx {275}*/
    MC virtual const std::string& getPlayerXUID(const mce::UUID&) const;

    /**@vidx {276}*/
    MC virtual const std::string& getPlayerPlatformOnlineId(const mce::UUID&) const;

    /**@vidx {277}*/
    MC virtual const std::vector<WeakEntityRef>& getActiveUsers() const;

    /**@vidx {278}*/
    MC virtual std::vector<Actor*> getRuntimeActorList() const;

    /**@vidx {279}*/
    MC virtual void _unknown_279();

    /**@vidx {280}*/
    MC virtual void _unknown_280();

    /**@vidx {281}*/
    MC virtual PacketSender* getPacketSender() const;

    /**@vidx {282}*/
    MC virtual void setPacketSender(PacketSender*);

    /**@vidx {283}*/
    MC virtual Bedrock::NonOwnerPointer<NetEventCallback> getNetEventCallback() const;

    /**@vidx {284}*/
    MC virtual void setNetEventCallback(Bedrock::NonOwnerPointer<NetEventCallback>);

    /**@vidx {285}*/
    MC virtual void _unknown_285();

    /**@vidx {286}*/
    MC virtual void _unknown_286();

    /**@vidx {287}*/
    MC virtual void _unknown_287();

    /**@vidx {288}*/
    MC virtual HitResult& getHitResult();

    /**@vidx {289}*/
    MC virtual HitResult& getLiquidHitResult();

    /**@vidx {290}*/
    MC virtual const std::string& getImmersiveReaderString() const;

    /**@vidx {291}*/
    MC virtual void setImmersiveReaderString(std::string);

    /**@vidx {292}*/
    MC virtual const AdventureSettings& getAdventureSettings() const;

    /**@vidx {293}*/
    MC virtual AdventureSettings& getAdventureSettings();

    /**@vidx {294}*/
    MC virtual GameRules& getGameRules();

    /**@vidx {295}*/
    MC virtual const GameRules& getGameRules() const;

    /**@vidx {296}*/
    MC virtual bool hasStartWithMapEnabled() const;

    /**@vidx {297}*/
    MC virtual bool isEditorWorld() const;

    /**@vidx {298}*/
    MC virtual Abilities& getDefaultAbilities();

    /**@vidx {299}*/
    MC virtual const PermissionsHandler& getDefaultPermissions() const;

    /**@vidx {300}*/
    MC virtual PermissionsHandler& getDefaultPermissions();

    /**@vidx {301}*/
    MC virtual bool getTearingDown() const;

    /**@vidx {302}*/
    MC virtual void takePicture(cg::ImageBuffer&, Actor*, Actor*, ScreenshotOptions&);

    /**@vidx {303}*/
    MC virtual gsl::not_null<Bedrock::NonOwnerPointer<LevelSoundManager>> getLevelSoundManager();

    /**@vidx {304}*/
    MC virtual gsl::not_null<Bedrock::NonOwnerPointer<SoundPlayerInterface>> getSoundPlayer() const;

    /**@vidx {305}*/
    MC virtual void setSimPaused(bool);

    /**@vidx {306}*/
    MC virtual bool getSimPaused();

    /**@vidx {307}*/
    MC virtual void setFinishedInitializing();

    /**@vidx {308}*/
    MC virtual LootTables& getLootTables();

    /**@vidx {309}*/
    MC virtual void updateWeather(float, int, float, int);

    /**@vidx {310}*/
    MC virtual int getNetherScale() const;

    /**@vidx {311}*/
    MC virtual void _unknown_311();

    /**@vidx {312}*/
    MC virtual void _unknown_312();

    /**@vidx {313}*/
    MC virtual void _unknown_313();

    /**@vidx {314}*/
    MC virtual LayeredAbilities* getPlayerAbilities(const ActorUniqueID&);

    /**@vidx {315}*/
    MC virtual void setPlayerAbilities(const ActorUniqueID&, const LayeredAbilities&);

    /**@vidx {316}*/
    MC virtual void sendAllPlayerAbilities(const Player&);

    /**@vidx {317}*/
    MC virtual Recipes& getRecipes() const;

    /**@vidx {318}*/
    MC virtual BlockReducer* getBlockReducer() const;

    /**@vidx {319}*/
    MC virtual void _unknown_319();

    /**@vidx {320}*/
    MC virtual void _unknown_320();

    /**@vidx {321}*/
    MC virtual void _unknown_321();

    /**@vidx {322}*/
    MC virtual void _unknown_322();

    /**@vidx {323}*/
    MC virtual void digestServerItemComponents(const ItemComponentPacket&);

    /**@vidx {324}*/
    MC virtual const BlockLegacy& getRegisteredBorderBlock() const;

    /**@vidx {325}*/
    MC virtual bool use3DBiomeMaps() const;

    /**@vidx {326}*/
    MC virtual void addBlockSourceForValidityTracking(BlockSource*);

    /**@vidx {327}*/
    MC virtual void removeBlockSourceFromValidityTracking(BlockSource*);

    /**@vidx {328}*/
    MC virtual Level* asLevel();

    /**@vidx {329}*/
    MC virtual void _unknown_329();

    /**@vidx {330}*/
    MC virtual bool isClientSideGenerationEnabled();

    /**@vidx {331}*/
    MC virtual bool blockNetworkIdsAreHashes();

    /**@vidx {332}*/
    MC virtual ItemRegistryRef getItemRegistry() const;

    /**@vidx {333}*/
    MC virtual std::weak_ptr<BlockTypeRegistry> getBlockRegistry() const;

    /**@vidx {334}*/
    MC virtual void pauseAndFlushTaskGroups();

    /**@vidx {335}*/
    MC virtual void _unknown_335();

    /**@vidx {336}*/
    MC virtual void _unknown_336();

    /**@vidx {337}*/
    MC virtual void _unknown_337();

    /**@vidx {338}*/
    MC virtual void _unknown_338();

    /**@vidx {339}*/
    MC virtual void _unknown_339();

protected:
    /**@vidx {340}*/
    MC virtual void _subTick();

    /**@vidx {341}*/
    MC virtual void _initializeMapDataManager();
};