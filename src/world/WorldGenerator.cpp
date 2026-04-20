#include "world/WorldGenerator.hpp"

#include <cmath>
#include <spdlog/spdlog.h>
#include <iostream>

#include "globals/Globals.hpp"
#include "tenshiUtil/math/Random.h"
#include "entities/Tree.hpp"

#pragma region Noise Helper Functions
TileType WorldGenerator::NoiseToTileType(f32 noise)
{
    if (noise < 0.0f)
    {
        return TileType::Water;
    }
    else if (noise > 0.0f)
    {
        return TileType::Land;
    }

    return TileType::Land;
}

void WorldGenerator::GenerateNoiseMap(f64** noiseMap, u32 w, u32 h, f32 frequency, f32 weight)
{
    for (i32 x = 0; x < w; x++)
    {
        for (i32 y = 0; y < h; y++)
        {
            f64 _nx = (f64)x * frequency;
            f64 _ny = (f64)y * frequency;

            f64 _val = m_NoiseGen.GetNoise(_nx, _ny) * weight;

            // Normalize to a Range of 0 - 1 since GetNoise is -1 to 1
            _val = (_val - -1.0f) / (1.0f - -1.0f);
            noiseMap[x][y] += _val;
        }
    }
}

Texture2D WorldGenerator::NoiseToTexture(f64** noiseMap, u32 w, u32 h)
{
    Color* _colorBuffer = (Color*)malloc(w * h * sizeof(Color));

    for (i32 x = 0; x < w; x++)
    {
        for (i32 y = 0; y < h; y++)
        {
            unsigned char brightness = (u8)(noiseMap[x][y] * 255.0f);

            _colorBuffer[y * w + x] = (Color){
                brightness,
                brightness,
                brightness,
                255
            };
        }
    }

    Image img = {
        .data = _colorBuffer,
        .width = (i32)w,
        .height = (i32)h,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    Texture2D texture = LoadTextureFromImage(img);

    delete _colorBuffer;

    return texture;
}
#pragma endregion Noise Helper Functions

#pragma region World Generation
void WorldGenerator::GenerateWorld()
{
    // Clear World if we regenerate
    if (m_WasWorldGenerated)
    {
        ClearWorld();
    }

    m_WasWorldGenerated = true;
}

void WorldGenerator::ClearWorld()
{
}
#pragma endregion World Generation

#pragma region Island
Island* WorldGenerator::GenerateIsland(Vector2Int size, Vector2 pos)
{
    Island* island = nullptr;
    Tile** tiles = new Tile*[size.x];

    f32 _scale = 0.045f;

    // First Pass: Terrain Gen
    for (i32 x = 0; x < size.x; x++)
    {
        tiles[x] = new Tile[size.y];
        for (i32 y = 0; y < size.y; y++)
        {
            Tile _tile;

            f32 _noise = m_NoiseGen.GetNoise(x * _scale, y * _scale);

            // Radial Falloff
            f32 _dx = (x - size.x * 0.5f) / (size.x * 0.5f);
            f32 _dy = (y - size.y * 0.5f) / (size.y * 0.5f);
            f32 _dist = sqrt(_dx * _dx + _dy * _dy);

            _dist *= 0.8f;
            _noise *= 2.34f;

            f32 _tileVal = _noise - _dist + 0.7f;

            _tile.m_Type = NoiseToTileType(_tileVal);

            switch (_tile.m_Type)
            {
            case TileType::Land:
                _tile.m_SpriteSheetIndex = SpriteSheets::GrassTiles;
                break;

            case TileType::Water:
                _tile.m_SpriteSheetIndex = SpriteSheets::WaterTiles;
                break;
            }

            tiles[x][y] = _tile;
        }
    }

    // Second Pass: Edge Detection
    for (i32 x = 0; x < size.x; x++)
    {
        for (i32 y = 0; y < size.y; y++)
        {
            if (!IsLand(tiles, x, y, size))
            {
                continue;
            }

            u8 _mask = CalculateEdgeMask(tiles, x, y, size);
            tiles[x][y].m_NeighbourMask = _mask;
            Vector2Int _index = GetSpriteFromTileMask(_mask);
            tiles[x][y].m_TileIndex = _index;
        }
    }

    // Third Pass: Generate Trees and Stones
    std::unordered_map<Vector2Int, Entity*> staticEntities;
    _scale = 0.35f;

    u32 _treeCounter = 0;
    for (i32 x = 0; x < size.x; x++)
    {
        for (i32 y = 0; y < size.y; y++)
        {
            if (!IsLand(tiles, x, y, size))
            {
                continue;
            }

            f32 _noise = m_NoiseGen.GetNoise(x * _scale, y * _scale) + 0.7f;
            spdlog::info("Noise at {} {} -> {}", x, y, _scale);
            if (_noise < 0.54f)
            {
                Tree* tree = g_EntityManager->CreateEntity<Tree>("Tree", TreeType::Plain);
                tree->m_Position = {(f32)x, (f32)y};
                staticEntities.insert({{x, y}, tree});
                ++_treeCounter;
            }
        }
    }

    spdlog::info("Generated {} Trees", _treeCounter);

    island = new Island(tiles, size, pos);
    for (auto& e : staticEntities)
    {
        island->AddStaticEntity(e.second, {(i32)e.first.x, (i32)e.first.y});
    }

    return island;
}

bool WorldGenerator::IsLand(Tile** tiles, i32 x, i32 y, Vector2Int size) const
{
    if (x < 0 || x >= size.x || y < 0 || y >= size.y)
    {
        return false;
    }

    return tiles[x][y].m_Type == TileType::Land;
}

u8 WorldGenerator::CalculateEdgeMask(Tile** tiles, u32 x, u32 y, Vector2Int size) const
{
    u8 _mask = 0;

    if (IsLand(tiles, x, y - 1, size)) { _mask |= TOP; }
    if (IsLand(tiles, x, y + 1, size)) { _mask |= BOTTOM; }
    if (IsLand(tiles, x + 1, y, size)) { _mask |= RIGHT; }
    if (IsLand(tiles, x - 1, y, size)) { _mask |= LEFT; }

    return _mask;
}

Vector2Int WorldGenerator::GetSpriteFromTileMask(u8 mask) const
{
    Vector2Int _index = {0, 0};

    switch (mask)
    {
    // TOP LEFT CORNER
    case BOTTOM | RIGHT:
        return TOP_LEFT_CORNER_INDEX;

    // TOP RIGHT CORNER
    case BOTTOM | LEFT:
        return TOP_RIGHT_CORNER_INDEX;

    // BOTTOM LEFT CORNER
    case TOP | RIGHT:
        return BOTTOM_LEFT_CORNER_INDEX;

    // BOTTOM RIGHT CORNER
    case TOP | LEFT:
        return BOTTOM_RIGHT_CORNER_INDEX;

    // TOP EDGE
    case BOTTOM | RIGHT | LEFT:
        return TOP_EDGE_INDEX;

    // BOTTOM EDGE
    case TOP | RIGHT | LEFT:
        return BOTTOM_EDGE_INDEX;

    // LEFT EDGE
    case TOP | BOTTOM | RIGHT:
        return LEFT_EDGE_INDEX;

    // RIGHT EDGE
    case TOP | BOTTOM | LEFT:
        return RIGHT_EDGE_INDEX;

    // CENTER
    case TOP | BOTTOM | LEFT | RIGHT:
        if (Random::GetInt(0, 5) <= 4)
            return {1, 1};
        else
            return {Random::GetInt(0, 5), Random::GetInt(5, 6)};
        break;

    default:
        return {1, 1};
    }
}

std::string WorldGenerator::MaskToStr(u8 mask)
{
    switch (mask)
    {
    // TOP LEFT CORNER
    case BOTTOM | RIGHT:
        return "Top Left Corner";

    // TOP RIGHT CORNER
    case BOTTOM | LEFT:
        return "Top Right Corner";

    // BOTTOM LEFT CORNER
    case TOP | RIGHT:
        return "Bottom Left Corner";

    // BOTTOM RIGHT CORNER
    case TOP | LEFT:
        return "Bottom Right Corner";

    // TOP EDGE
    case BOTTOM | RIGHT | LEFT:
        return "Top Edge";

    // BOTTOM EDGE
    case TOP | RIGHT | LEFT:
        return "Bottom Edge";

    // LEFT EDGE
    case TOP | BOTTOM | RIGHT:
        return "Left Edge";

    // RIGHT EDGE
    case TOP | BOTTOM | LEFT:
        return "Right Edge";

    default:
        return "Center";
    }
}
#pragma endregion Island
