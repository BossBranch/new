#pragma once
#include <vector>

class Item;
class Block;
class BlockDescriptor;

class SeedItemComponentLegacy {
public:
	Item& mOwner;
	Block const& mResult;
	std::vector<BlockDescriptor> mTargetLandBlocks;
	bool mPlantAtAnyVisibleSolidSurface;
	bool mIsPlanting;
	unsigned char mFaceToPlantAt;
};