#pragma once
#include "BlockLegacy.hpp"

class ActorBlock : public BlockLegacy {
public:
    ActorBlock(const std::string& nameId, short id, const Material& material) : BlockLegacy(nameId, id, material) {}

    /// @vidx {inherit}
    virtual ~ActorBlock() override = default;

    /// @vidx {inherit}
    void neighborChanged(BlockSource& region, const BlockPos& pos, const BlockPos& neighborPos) const override;
    
    /// @vidx {inherit}
    void triggerEvent(BlockSource& region, const BlockPos& pos, int b0, int b1) const override;
};