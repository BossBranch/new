/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/AppPlatformListener.hpp>
#include <mc/src/common/world/level/LevelSettings.hpp>
#include <mc/src-deps/core/utility/UUID.hpp>
#include <mc/src-deps/gamerefs/OwnerPtr.hpp>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>

class IMinecraftApp;
class Minecraft;
class ServerNetworkSystem;
class GameCallbacks {};
class LoopbackPacketSender;
class Timer;
class Scheduler;
class EducationOptions;
class LevelStorage;
class AllowList;
class PermissionsFile;
struct ConnectionDefinition;
class LevelData;
class IMinecraftEventing;
class IResourcePackRepository;
class IContentTierManager;
class ResourcePackManager;
class ServerMetrics;
class DebugEndPoint;
struct NetworkSettingOptions;
struct PlayerMovementSettings;
struct ScriptSettings;
class Experiments;
struct NetworkPermissions;
class NetworkSessionOwner;
class CDNConfig;
class ServerTextSettings;

namespace Core {
	class StorageAreaStateListener {};
	class FilePathManager {};
	class FileStorageArea {};
};

namespace cereal {
	struct ReflectionCtx {};
}

class ServerInstance : public Bedrock::EnableNonOwnerReferences, public AppPlatformListener, public GameCallbacks, Core::StorageAreaStateListener {
public:
	std::chrono::steady_clock::time_point mLastSyncTime;
	IMinecraftApp const& mApp;
	std::unique_ptr<Minecraft> mMinecraft;
	std::unique_ptr<ServerNetworkSystem> mNetwork;
	std::unique_ptr<LoopbackPacketSender> mPacketSender;
	std::unique_ptr<Timer> mSimTimer;
	std::unique_ptr<Timer> mRealTimer;
	std::unique_ptr<Scheduler> mScheduler;
	std::unique_ptr<EducationOptions> mEducationOptions;
	LevelStorage* mStorage;
	std::atomic<bool> mInUpdate;
	std::atomic<int> mWriteRefCounter;
	std::atomic<bool> mThreadShouldJoin;
private:
	char pad[0x1BF];
public:
	std::string mLevelId;
	std::string mServerName;

public:
	/// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 89 95 ? ? ? ? 4C 8B E1}
	MC bool initializeServer(
		IMinecraftApp& app,
		AllowList& allowList,
		PermissionsFile* permissionsFile,
		Bedrock::NotNullNonOwnerPtr<Core::FilePathManager> const& pathManager,
		std::chrono::seconds maxPlayerIdleTime,
		std::string levelId,
		std::string levelName,
		std::string serverName,
		LevelSettings levelSettings,
		int maxChunkRadius,
		bool shouldAnnounce,
		ConnectionDefinition connectionDefinition,
		bool requireTrustedAuthentication,
		std::vector<std::string> const& extraTrustedKeys,
		std::string serverType,
		mce::UUID const& localPlayerId,
		IMinecraftEventing& eventing,
		Bedrock::NotNullNonOwnerPtr<IResourcePackRepository> const& resourcePackRepository,
		Bedrock::NotNullNonOwnerPtr<IContentTierManager const> const& contentTierManager,
		ResourcePackManager& clientResourcePackManager,
		std::function<OwnerPtr<LevelStorage>(Scheduler &)> createLevelStorageCallback,
		std::string const& basePath,
		LevelData* levelData,
		std::string playerSafetyServiceTextProcessorConfig,
		std::string serverId,
		std::string applicationId,
		std::string applicationSecret,
		std::string applicationTenantId,
		std::unique_ptr<EducationOptions> educationOptions,
		ResourcePackManager* localServerResourcePackManager,
		std::function<void()> criticalSaveCallback,
		std::function<void()> compactionCallback,
		ServerMetrics* serverMetrics,
		DebugEndPoint* debugEndPoint,
		bool enableWorldSessionEndPoint,
		std::shared_ptr<Core::FileStorageArea> storageAreaForLevel,
		NetworkSettingOptions const& networkSettings,
		bool enableItemStackNetManager,
		bool enableItemTransactionLogger,
		bool enableRealmsStories,
		std::optional<PlayerMovementSettings> playerMovementSettings,
		std::optional<ScriptSettings> scriptSettings,
		Experiments const& levelExperiments,
		bool isServerVisibleToLanDiscovery,
		float worldSizeMB,
		std::optional<bool> clientSideGenerationEnabled,
		ForceBlockNetworkIdsAreHashes blockNetworkIdsAreHashes,
		NetworkPermissions const& networkPermissions,
		Bedrock::NotNullNonOwnerPtr<NetworkSessionOwner> networkSessionOwner,
		Bedrock::NonOwnerPointer<CDNConfig> cdnConfig,
		cereal::ReflectionCtx& reflectionContext,
		Bedrock::NonOwnerPointer<ServerTextSettings> serverTextSettings
	);

	/// @signature {40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B DA 48 89 54 24 ? 8B 81 ? ? ? ? 90 83 F8 ? 74}
	MC void _threadSafeExecute(std::function<void()> func);

	/// @signature {48 89 5C 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 48 C7 44 24 ? ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 54 24 ? 48 8B CB E8 ? ? ? ? 90}
	MC void queueForServerThread(std::function<void()> func);
};