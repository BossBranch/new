#include <mc/src/common/network/packet/Packet.hpp>

Packet::Packet() {
    mPriority = MEDIUM_PRIORITY;
    mReliability = NetworkPeer::Reliability::ReliableOrdered;
    mClientSubId = SubClientId::PrimaryClient;
    mIsHandled = false;
    mReceiveTimepoint = std::chrono::steady_clock::time_point::min();
    mHandler = 0;
    mCompressible = Compressibility::Compressible;
}