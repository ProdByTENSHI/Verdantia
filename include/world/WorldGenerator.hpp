#pragma once

#include "raylib.h"
#include "world/Chunk.hpp"
#include "tenshiUtil/math/Vector2Int.hpp"
#include "tenshiUtil/math/PerlinNoise.hpp"

#include <unordered_map>

class WorldGenerator {
public:
    WorldGenerator() : m_GenerationSeed(4293184603) {
        m_NoiseGen.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        m_NoiseGen.SetSeed(1337);
    }

    WorldGenerator(u32 seed) : m_GenerationSeed(seed) {
        m_NoiseGen.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        m_NoiseGen.SetSeed(m_GenerationSeed);
    }

    ~WorldGenerator() {
    }

    void SetSeed(i32 seed) {
        m_NoiseGen.SetSeed(seed);
        m_GenerationSeed = seed;
    }

    void GenerateNoiseMap(f64** noiseMap, u32 w, u32 h, f32 frequency, f32 weight = 1.0f);

    Texture2D NoiseToTexture(f64 **noiseMap, u32 w, u32 h);

    // Returns the Tile Type by the Noise Value
    TileType NoiseToTileType(f32 noise);

public:
    void GenerateWorld();
    void ClearWorld();

    // pos = Position of the Islands Center Tile
    Tile** GenerateIsland(Vector2Int pos, Vector2Int size, f32 frequency);

    Tile** m_Tiles;

private:
    u32 m_GenerationSeed = 0;

    FastNoiseLite m_NoiseGen;

    bool m_WasGenerated = false;
};
