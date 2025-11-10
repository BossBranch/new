#pragma once
#include <cstddef>
#include <variant>

class ClientNetworkSystem;
class ServerNetworkSystem;

class ClientOrServerNetworkSystemRef 
    : public std::variant<std::reference_wrapper<ClientNetworkSystem>, std::reference_wrapper<ServerNetworkSystem>> {
public:
    using ClientRefT = std::reference_wrapper<ClientNetworkSystem>;
    using ServerRefT = std::reference_wrapper<ServerNetworkSystem>;
};