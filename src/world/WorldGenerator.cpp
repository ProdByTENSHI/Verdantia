#include "world/WorldGenerator.hpp"

#include <cmath>
#include <spdlog/spdlog.h>
#include <iostream>

#include "globals/Globals.hpp"

TileType WorldGenerator::NoiseToTileType(f32 noise) {
    if (noise < 0.5f) {
        return TileType::Water;
    } else if (noise > 0.51f) {
        return TileType::Grassland;
    }

    return TileType::Grassland;
}

// Each Tile corresponds to one Biome
void WorldGenerator::GenerateNoiseMap(f64** noiseMap, u32 w, u32 h, f32 frequency, f32 weight) {
    for (i32 x = 0; x < w; x++) {
        for (i32 y = 0; y < h; y++) {
            f64 _nx = (f64) x * frequency;
            f64 _ny = (f64) y * frequency;

            f64 _val = m_NoiseGen.GetNoise(_nx, _ny) * weight;

            // Normalize to a Range of 0 - 1 since GetNoise is -1 to 1
            _val = (_val - -1.0f) / (1.0f - -1.0f);
            noiseMap[x][y] += _val;
        }
    }
}

Texture2D WorldGenerator::NoiseToTexture(f64 **noiseMap, u32 w, u32 h) {
    Texture2D texture;
    Color *_colorBuffer = (Color*)malloc(w * h * sizeof(Color));

    for (i32 x = 0; x < w; x++) {
        for (i32 y = 0; y < h; y++) {
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

    texture = LoadTextureFromImage(img);

    delete _colorBuffer;

    return texture;
}

void WorldGenerator::GenerateWorld() {
    // Clear World if we regenerate
    if (m_WasGenerated) {
        ClearWorld();
    }

    // First Step of World Generation is to fill entire Screen with Water
    m_Tiles = new Tile* [g_WindowWidth];

    for (i32 x = 0; x < g_WindowWidth; x++) {
        m_Tiles[x] = new Tile[g_WindowHeight];
        for (i32 y = 0; y < g_WindowHeight; y++) {
            m_Tiles[x][y].m_Type = TileType::Water;
        }
    }

    m_WasGenerated = true;
}

void WorldGenerator::ClearWorld() {
    for (i32 i = 0; i < g_WindowWidth; i++) {
        delete[] m_Tiles[i];
    }

    delete[] m_Tiles;
}

Tile** WorldGenerator::GenerateIsland(Vector2Int pos, Vector2Int size, f32 frequency) {
    Tile** tiles = new Tile*[size.x];

    for (i32 x = 0; x < size.x; x++) {
        tiles[x] = new Tile[size.y];
        for (i32 y = 0; y < size.y; y++) {
            // 1. Create Falloff Mask so we get one big Island
            f32 _dx = (x - (size.x * 0.5f)) / (size.x * 0.5f);
            f32 _dy = (y - (size.y * 0.5f)) / (size.y * 0.5f);

            // Calc the distance from the Island Center to this Tile
            f32 _dist = sqrt(_dx * _dx + _dy * _dy);
            f32 _fallOff = 1.0f - _dist;

            // 2. Mix with Noise
            f64 _noise = m_NoiseGen.GetNoise((f32)x * frequency, (f32)y * frequency);

            f64 _finalVal = _noise + _fallOff;

            Tile _tile;
            _tile.m_Type = NoiseToTileType(_finalVal);
            tiles[x][y] = _tile;
            m_Tiles[x+pos.x][y+pos.y] = _tile;
        }
    }

    return tiles;
}
