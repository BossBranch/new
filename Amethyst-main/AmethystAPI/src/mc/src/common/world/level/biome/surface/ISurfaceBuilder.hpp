#pragma once
#include <BlockVolume.hpp>
#include <mc/src-deps/core/math/DividedPos2d.h>
#include <optional>

class Biome;
class Random;
class SurfaceNoiseCache;
class HeightMapWrapper;

class ISurfaceBuilder {
    class BuildParameters {
    public:
        Biome* biome;                                     // +0x00
        Random* random;                                   // +0x08
        BlockVolume* blockVolume;                         // +0x10
        BlockPos* blockPos;                               // +0x18
        float noiseValue;                                 // +0x20
        short seaLevel;                                   // +0x24
        std::unique_ptr<SurfaceNoiseCache>* surfaceNoise; // +0x28
        int waterLevelStrategy;                           // +0x30
        int surfaceHeight;                                // +0x34
        HeightMapWrapper* heightmapWrapper;               // +0x38
        bool cavesAndCliffsCompatible;                    // +0x40

        BuildParameters(
            Biome* biome,
            Random* random,
            BlockVolume* blockVolume,
            BlockPos* blockPos,
            float noiseValue,
            short seaLevel,
            std::unique_ptr<SurfaceNoiseCache>* surfaceNoise,
            int waterLevelStrategy,
            int surfaceHeight,
            HeightMapWrapper* heightmapWrapper,
            bool cavesAndCliffsCompatible)
            : biome(biome), random(random), blockVolume(blockVolume), blockPos(blockPos), noiseValue(noiseValue), seaLevel(seaLevel), surfaceNoise(surfaceNoise), waterLevelStrategy(waterLevelStrategy), surfaceHeight(surfaceHeight), heightmapWrapper(heightmapWrapper), cavesAndCliffsCompatible(cavesAndCliffsCompatible)
        {
        }
    };
};