#include "mc/src/common/world/level/block/Block.hpp"
#include "mc/src/common/world/level/block/BlockLegacy.hpp"
#include "mc/src/common/world/phys/AABB.hpp"
#include "mc/src/common/world/Facing.hpp"

template <typename T>
inline T Block::getState(const BlockState& blockState) const
{
    auto& states = mLegacyBlock->mStates;
    auto result = states.find(blockState.mID);

    if (blockState.mID >= result->first) {
        int value = (0xFFFF >> (16 - result->second.mNumBits)) & (mData >> (result->second.mEndBit - result->second.mNumBits + 1));
		return static_cast<T>(value);
    }

    auto alteredState = mLegacyBlock->_tryLookupAlteredStateCollection(blockState.mID, mData);

    if (alteredState.has_value()) 
		return static_cast<T>(alteredState.value());

    return static_cast<T>(0);
}

template int Block::getState<int>(const BlockState& blockState) const;
template Facing::Axis Block::getState<Facing::Axis>(const BlockState& blockState) const;
template FacingID Block::getState<FacingID>(const BlockState& blockState) const;

template <typename T>
gsl::strict_not_null<const Block*> Block::setState(const BlockState& stateType, T value) const {
    auto& states = mLegacyBlock->mStates;
    auto foundState = states.find(stateType.mID);

    if (stateType.mID >= foundState->first) {
        if ((int)value < (int64_t)foundState->second.mVariationCount) {
            uint64_t maskedData = mData & (~foundState->second.mMask);
            uint64_t index = maskedData | ((int)value << (foundState->second.mEndBit - foundState->second.mNumBits + 1));

            if (index < mLegacyBlock->mBlockPermutations.size()) {
                return gsl::make_not_null(mLegacyBlock->mBlockPermutations[index].get());
            }
        }
        else {
            Log::Info("more than found variation count");
        }

        AssertFail("Not handling this ong!");
    }

	AssertFail("Unhandled case in Block::setState");
}

template gsl::strict_not_null<const Block*> Block::setState<int>(const BlockState& stateType, int value) const;
template gsl::strict_not_null<const Block*> Block::setState<Facing::Axis>(const BlockState& stateType, Facing::Axis value) const;
template gsl::strict_not_null<const Block*> Block::setState<FacingID>(const BlockState& stateType, FacingID value) const;

bool Block::hasState(const BlockState& stateType) const {
    auto& states = mLegacyBlock->mStates;
	auto foundState = states.find(stateType.mID);
	return foundState != states.end();
}

// 1.20.71.1 - Partial reimplementation using `BlockLegacy::getMapColor`
mce::Color Block::getMapColor(BlockSource& region, const BlockPos& pos) const
{
    return this->mLegacyBlock->getMapColor(region, pos, *this);
}

bool Block::canBeBuiltOver(BlockSource& region, const BlockPos& pos) const {
    return mLegacyBlock->canBeBuiltOver(region, pos);
}

bool Block::isAir() const {
    return mLegacyBlock->isAir();
}

bool Block::isFenceBlock() const
{
    return mLegacyBlock->isFenceBlock();
}

bool Block::getCollisionShape(AABB& outAABB, const IConstBlockSource& region, const BlockPos& pos, optional_ref<const GetCollisionShapeInterface> entity) const
{
    outAABB = this->mLegacyBlock->getCollisionShape(*this, region, pos, entity);
    return outAABB.min.x < outAABB.max.x && outAABB.min.y < outAABB.max.y && outAABB.min.z < outAABB.max.z;
}

const Material& Block::getMaterial() const
{
    return mLegacyBlock->mMaterial;
}

bool Block::isInteractiveBlock() const
{
    using function = decltype(&Block::isInteractiveBlock);
    static auto func = std::bit_cast<function>(SigScan("40 53 48 83 EC ? 48 8B D9 48 8B 49 ? 48 85 C9 74 ? F6 81"));
    return (this->*func)();
}

bool Block::hasProperty(BlockProperty property) const
{
    return mLegacyBlock->hasProperty(property);
}

bool Block::requiresCorrectToolForDrops() const {
    if (!mLegacyBlock)
		AssertFail("mLegacyBlock is null");
	return !mLegacyBlock->mMaterial.mAlwaysDestroyable && !mLegacyBlock->mCanDropWithAnyTool;
}