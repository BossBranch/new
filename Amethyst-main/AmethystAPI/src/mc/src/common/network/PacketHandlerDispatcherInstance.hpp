#pragma once
#include <mc/src/common/network/IPacketHandlerDispatcher.hpp>

template <typename Packet, bool Unk = false> 
class PacketHandlerDispatcherInstance : public IPacketHandlerDispatcher {
public:
    virtual void handle(const NetworkIdentifier&, NetEventCallback&, std::shared_ptr<Packet>& packet) const;
};