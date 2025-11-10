#pragma once
#include <cstdint>
#include <mc/src-client/common/client/world/LocalWorldStarter.hpp>

namespace World {

class System {
public:
    std::byte padding0[1488];
    World::LocalWorldStarter mLocalWorldStarter;
};

}
