///@symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/actor/ActorType.hpp>

class ActorGoalFactory;
class ActorDefinitionGroup;
struct ActorDefinitionIdentifier;
class Experiments;
class CompoundTag;
class LevelChunk;
class BlockSource;
class DataLoadHelper;
class DimensionHeightRange;
class ActorFactoryData;
class IEntityInitializer;
class Level;
class ActorInfo;
class Actor;

class ActorFactory {
public:
	/// @vidx {0}
	MC virtual ~ActorFactory();

//begin members:
	ActorFactory(gsl::not_null<Bedrock::NonOwnerPointer<Level>>);

	ActorGoalFactory& getGoalFactory();

	void setDefinitionGroup(ActorDefinitionGroup* unk0);

	void setEntityInitializer(std::shared_ptr<IEntityInitializer> unk0);

	bool hasActor(const ActorDefinitionIdentifier& unk0, ActorType unk1) const;

	std::vector<std::pair<std::string, const ActorDefinitionIdentifier*>> buildSummonEntityTypeEnum(const Experiments& unk0) const;

	UnknownReturn buildUniqueSummonableActorList(const Experiments& unk0) const;

	void _buildSummonableActorList(const Experiments& unk0, std::function<void(const std::string&, const ActorFactoryData&)> unk1) const;

	/// @signature {40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 89 4C 24}
	MC OwnerPtr<EntityContext> _constructActor(const ActorDefinitionIdentifier& unk0, const Vec3& unk1, const Vec2& unk2, const std::vector<std::string>* unk3) const;

	void _loadDefinitionGroups(ActorDefinitionGroup* unk0);

	void _loadDefinitionsHelper();

	/// @signature {40 55 53 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B D9}
	MC bool _validateActorData(CompoundTag& unk0, ActorDefinitionIdentifier& unk1, Vec3& unk2, const LevelChunk* unk3) const;

	/// @signature {48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 49 8B E8 48 8B DA 48 8B F9}
	MC void applyEntityInitializer(std::unique_ptr<Actor> unk0, EntityContext& unk1) const;

	void clearDefinitionGroup();

	static void clearEntityMappings();

	OwnerPtr<EntityContext> clientCreateDisplayActor(const ActorDefinitionIdentifier& unk0, Actor* unk1, const Vec3& unk2, const Vec2& unk3);

	/// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 49 8B F1 49 8B F8}
	MC OwnerPtr<EntityContext> createActor(const std::string& unk0, const ActorDefinitionIdentifier& unk1, Actor* unk2, const Vec3& unk3, const Vec2& unk4);

	/// @signature {48 8B C4 53 55 56 57 41 55 41 56 48 81 EC}
	MC OwnerPtr<EntityContext> createBornActor(const ActorDefinitionIdentifier& unk0, Actor* unk1);

	/// @signature {48 8B C4 48 89 58 ? 48 89 70 ? 48 89 50 ? 57 48 83 EC ? 49 8B F0}
	MC OwnerPtr<EntityContext> createBornActor(const ActorDefinitionIdentifier& unk0, const BlockPos& unk1);

	/// @signature {40 53 55 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4D 8B E1 49 8B E8 48 8B DA}
	MC OwnerPtr<EntityContext> createSpawnedActor(const ActorDefinitionIdentifier& unk0, Actor* unk1, const Vec3& unk2, const Vec2& unk3);

	/// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 84 24 ? ? ? ? 48 8B E9 49 8D 48}
	MC OwnerPtr<EntityContext> createSummonedActor(const ActorDefinitionIdentifier& unk0, Actor* unk1, const Vec3& unk2);

	/// @signature {40 53 55 56 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B F1 49 8B E8}
	MC OwnerPtr<EntityContext> createTransformedActor(const ActorDefinitionIdentifier& unk0, Actor* unk1);

	UnknownReturn digestIdentifierListFromServer(const std::vector<ActorInfo>& unk0);

	/// @signature {40 53 55 56 57 48 83 EC ? 48 8B DA}
	MC static void fillFactoryData(const ActorDefinitionIdentifier& unk0, const ActorDefinitionIdentifier& unk1, const std::unordered_map<std::string, ActorFactoryData, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<const std::string, ActorFactoryData>>>& unk2, ActorFactoryData& unk3);

	/// @signature {48 89 5C 24 ? 55 56 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B DA 48 8B F9 48 85 D2}
	MC static Actor* fixLegacyEntity(BlockSource& unk0, const CompoundTag* unk1);

	UnknownReturn generateActorIdentifierList() const;

	void init(const Experiments& unk0);

	/// @signature {40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 89 4C 24 ? 4D 8B E0 48 8B FA}
	MC OwnerPtr<EntityContext> loadActor(CompoundTag* unk0, DataLoadHelper& unk1, const DimensionHeightRange& unk2, const LevelChunk* unk3);

	OwnerPtr<EntityContext> loadActor(CompoundTag* unk0, DataLoadHelper& unk1, const DimensionHeightRange& unk2);

	OwnerPtr<EntityContext> loadActor(CompoundTag* unk0, DataLoadHelper& unk1);

	/// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 48 8B 79 ? 48 8B 1F}
	MC ActorType lookupEntityType(const ActorDefinitionIdentifier& unk0) const;

	/// @signature {48 83 EC ? 8B 01 89 44 24}
	MC static void registerEntityMapping(
		ActorType const& actorType,
		bool allowSummon,
		void* a3,
		std::optional<int> experimentIndex
	);
};