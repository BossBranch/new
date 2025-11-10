#pragma once
#include <amethyst/Memory.hpp>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <map>
#include <mc/src-deps/core/utility/pubsub/Publisher.hpp>
#include <mc/src-deps/core/utility/pubsub/detail/ThreadingPublisherBase.hpp>
#include <mc/src-deps/core/string/StringHash.hpp>

enum class GameRulesIndex : int {
    InvalidGameRule           = -1,
    CommandBlockOutput        = 0,
    DoDaylightCycle           = 1,
    DoEntityDrops             = 2,
    DoFireTick                = 3,
    RecipesUnlock             = 4,
    DoLimitedCrafting         = 5,
    DoMobLoot                 = 6,
    DoMobSpawning             = 7,
    DoTileDrops               = 8,
    DoWeatherCycle            = 9,
    DrowningDamage            = 10,
    FallDamage                = 11,
    FireDamage                = 12,
    KeepInventory             = 13,
    MobGriefing               = 14,
    Pvp                       = 15,
    ShowCoordinates           = 16,
    LocatorBar                = 17,
    ShowDaysPlayed            = 18,
    DoNaturalRegeneration     = 19,
    DoTntExplode              = 20,
    SendCommandFeedback       = 21,
    MaxCommandChainLength     = 22,
    DoInsomnia                = 23,
    CommandBlocksEnabled      = 24,
    RandomTickSpeed           = 25,
    DoImmediateRespawn        = 26,
    ShowDeathMessages         = 27,
    FunctionCommandLimit      = 28,
    PlayerSpawnRadius         = 29,
    ShowTags                  = 30,
    FreezeDamage              = 31,
    RespawnBlocksExplode      = 32,
    ShowBorderEffect          = 33,
    ShowRecipeMessages        = 34,
    PlayerSleepingPercentage  = 35,
    ProjectilesCanBreakBlocks = 36,
    TntExplosionDropDecay     = 37,
    VanillaGameRuleCount      = 38,
    GlobalMute                = 38,
    AllowDestructiveObjects   = 39,
    AllowMobs                 = 40,
    CodeBuilder               = 41,
    EduCloudSave              = 42,
    EduGameRuleCount          = 43,
    GameRuleCount             = 43,
};

class GameRule {
public:
    /* this + 0  */ std::byte padding0[4];
    /* this + 4  */ bool mEnabled;
    /* this + 5  */ std::byte padding5[3];
    /* this + 8  */ std::string mName;
    /* this + 40 */ std::byte padding40[3];
    /* this + 43 */ bool mRequiresCheats;
    /* this + 44 */ std::byte padding44[132];
};

class GameRuleId;

class GameRules : public Bedrock::EnableNonOwnerReferences {
public:
    std::vector<GameRule> mGameRules;
    std::map<HashedString, GameRule> mWorldPolicies;
    //Bedrock::PubSub::Publisher<void(const GameRules&, const GameRuleId&), Bedrock::PubSub::ThreadModel::MultiThreaded> mGameRuleChangePublisher;
    std::byte mGameRuleChangePublisher[128];

    // 1.21.0.3 - 48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B F9 48 83 C1
    void _registerRules();
};