#pragma once

#include "tenshiUtil/Types.h"
#include "tenshiUtil/math/Vector2Int.hpp"

constexpr u32 TILE_SIZE = 16;

// Chunks are 16 x 16 Tiles
constexpr u32 TILES_PER_CHUNK = 16;

constexpr f32 TIME_BETWEEN_ANIM_TICKS = 0.1f;

enum class RenderLayer : u8
{
    Ground = 0,
    Entities = 1
};

enum class TextureType : u8
{
    GroundTile,
    Building,
    AnimalBuilding,
    Object,
    Player,
    Animal
};

// 1, 0 -> Right
// -1, 0 -> Left
// 0, -1 -> Top
// 0, 1 -> Bottom
const Vector2Int RIGHT_DIR = Vector2Int(1, 0);
const Vector2Int LEFT_DIR = Vector2Int(-1, 0);
const Vector2Int UP_DIR = Vector2Int(0, -1);
const Vector2Int DOWN_DIR = Vector2Int(0, 1);
