#pragma once

#include "tenshiUtil/Types.h"

constexpr u32 TILE_SIZE = 16;

// Chunks are 16 x 16 Tiles
constexpr u32 TILES_PER_CHUNK = 16;

constexpr f32 TIME_BETWEEN_ANIM_TICKS = 0.1f;

enum class RenderLayer : u8 {
    Ground = 0,
    Entities = 1
};

enum class TextureType : u8 {
    GroundTile,
    Building,
    AnimalBuilding,
    Object,
    Player,
    Animal
};