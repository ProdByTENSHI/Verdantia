#pragma once

#include "world/Tile.hpp"

#include <vector>
#include <raylib.h>

#include "tenshiUtil/math/Vector2Int.hpp"

struct Chunk {
    Chunk() {
    }

    bool m_ShouldBeSerialized = false;
    bool m_WasLoadedBefore = false;

    Vector2Int m_Position = {0, 0};
    Tile m_Tiles[TILES_PER_CHUNK][TILES_PER_CHUNK];

    bool operator==(const Chunk &rhs) const {
        return m_Position == rhs.m_Position;
    }
};
