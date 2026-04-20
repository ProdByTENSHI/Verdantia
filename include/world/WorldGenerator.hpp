#pragma once

#include "raylib.h"
#include "world/Chunk.hpp"
#include "tenshiUtil/math/Vector2Int.hpp"
#include "tenshiUtil/math/PerlinNoise.hpp"

#include <unordered_map>
#include <string>
#include "world/Island.hpp"

class WorldGenerator
{
public:
#pragma region Ctor
    WorldGenerator() : m_GenerationSeed(4293184603)
    {
        m_NoiseGen.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        m_NoiseGen.SetSeed(1337);
        m_NoiseGen.SetFrequency(1.0f);
    }

    WorldGenerator(u32 seed) : m_GenerationSeed(seed)
    {
        m_NoiseGen.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        m_NoiseGen.SetSeed(m_GenerationSeed);
        m_NoiseGen.SetFrequency(1.0f);
    }

    ~WorldGenerator()
    {
    }
#pragma endregion Ctor

#pragma region Noise Helper Functions
    void SetSeed(i32 seed)
    {
        m_NoiseGen.SetSeed(seed);
        m_GenerationSeed = seed;
    }

    void GenerateNoiseMap(f64** noiseMap, u32 w, u32 h, f32 frequency, f32 weight = 1.0f);

    Texture2D NoiseToTexture(f64** noiseMap, u32 w, u32 h);

    // Returns the Tile Type by the Noise Value
    TileType NoiseToTileType(f32 noise);
#pragma endregion Noise Helper Functions

public:
#pragma region World Generation
    void GenerateWorld();

    void ClearWorld();
#pragma endregion World Generation

#pragma region Island
    // pos = Position of the Islands Center Tile
    Island* GenerateIsland(Vector2Int size, Vector2 pos);

    bool IsLand(Tile** tiles, i32 x, i32 y, Vector2Int size) const;

    u8 CalculateEdgeMask(Tile** tiles, u32 x, u32 y, Vector2Int size) const;

    Vector2Int GetSpriteFromTileMask(u8 mask) const;

    static std::string MaskToStr(u8 mask);
#pragma endregion Island

private:
    u32 m_GenerationSeed = 0;

    FastNoiseLite m_NoiseGen;

    bool m_WasWorldGenerated = false;
};
