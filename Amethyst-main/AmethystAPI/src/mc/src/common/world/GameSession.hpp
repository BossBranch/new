#pragma once
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <mc/src/common/network/ClientOrServerNetworkSystemRef.hpp>
#include <mc/src-deps/gamerefs/OwnerPtr.hpp>
#include <mc/src/common/CommonTypes.hpp>
#include <mc/src/common/world/level/Level.hpp>

class EntityContext;
class Level;
class NetEventCallback;
class ServerNetworkHandler;
class LoopbackPacketSender;

struct GameSession {
public:
    /* this + 0  */ ClientOrServerNetworkSystemRef mNetwork;
    /* this + 16 */ std::byte padding_mLevelEntity[32]; // OwnerPtr<EntityContext>
    /* this + 48 */ Bedrock::NonOwnerPointer<Level> mLevel;
    /* this + 56 */ std::unique_ptr<ServerNetworkHandler> mServerNetworkHandler;
    /* this + 64 */ std::unique_ptr<NetEventCallback> mLegacyClientNetworkHandler;
    /* this + 80 */ std::unique_ptr<NetEventCallback> mClientNetworkHandler;
    /* this + 88 */ LoopbackPacketSender* mLoopbackPacketSender;
    /* this + 96 */ SubClientId mClientSubId;
};