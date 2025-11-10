/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/level/dimension/Dimension.hpp>

/**@vptr {0x4EE8900} */
/**@vptr {0x4E5FA10, SavedData} */
/**@vptr {0x4E5FA28, LevelListener} */
class OverworldDimension : public Dimension {
public:
    /** @vidx {i} */
	MC virtual ~OverworldDimension() override;

	/** @vidx {i} */
    MC virtual Vec3 translatePosAcrossDimension(const Vec3&, DimensionType) const override;

    /** @vidx {i} */
	MC virtual std::unique_ptr<class WorldGenerator> createGenerator(const br::worldgen::StructureSetRegistry&) override;

    /** @vidx {i} */
	MC virtual void upgradeLevelChunk(class ChunkSource& source, class LevelChunk& lc, class LevelChunk& generatedChunk) override;

    /** @vidx {i} */
	MC virtual void fixWallChunk(class ChunkSource&, class LevelChunk&) override;

    /** @vidx {i} */
	MC virtual bool levelChunkNeedsUpgrade(const LevelChunk&) const override;

	/** @vidx {i} */
    MC virtual class mce::Color getBrightnessDependentFogColor(const mce::Color& baseColor, float brightness) const override;

	/** @vidx {i} */
    MC virtual bool hasPrecipitationFog() const override;

	/** @vidx {i} */
    MC virtual short getCloudHeight() const override;

    /** @vidx {i} */
	MC virtual void _upgradeOldLimboEntity(class CompoundTag& tag, LimboEntitiesVersion vers) override;

    /** @vidx {i} */
	MC virtual std::unique_ptr<class ChunkSource> _wrapStorageForVersionCompatibility(std::unique_ptr<class ChunkSource> storageSource, StorageVersion levelVersion) override;

	/// @sig {4C 8B DC 49 89 5B ? 55 56 57 48 83 EC ? 49 8B D8}
	MC OverworldDimension(ILevel& level, Scheduler& callbackContext);

	// made up constructor to set a custom dimID
    // OverworldDimension(ILevel& level, DimensionType dimId, DimensionHeightRange heightRange, Scheduler& callbackContext, std::string dimensionName) 
		//: Dimension(level, dimId, heightRange, callbackContext, dimensionName) {}
};