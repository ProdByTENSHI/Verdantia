#pragma once

#include "globals/Constants.hpp"
#include "tenshiUtil/math/Vector2Int.hpp"
#include <raylib.h>

// Tile Spritesheet Indices
const Vector2Int TOP_LEFT_CORNER_INDEX = {0, 0};
const Vector2Int TOP_EDGE_INDEX = {1, 0};
const Vector2Int TOP_RIGHT_CORNER_INDEX = {2, 0};

const Vector2Int LEFT_EDGE_INDEX = {0, 1};
const Vector2Int RIGHT_EDGE_INDEX = {2, 1};

const Vector2Int BOTTOM_LEFT_CORNER_INDEX = {0, 2};
const Vector2Int BOTTOM_EDGE_INDEX = {1, 2};
const Vector2Int BOTTOM_RIGHT_CORNER_INDEX = {2, 2};

// Bitmask to check wether the Neighbours are Land or Water
constexpr u8 TOP = 1;
constexpr u8 RIGHT = 2;
constexpr u8 BOTTOM = 4;
constexpr u8 LEFT = 8;

// Tile Values
// 0.0 - 0.5 = Water
// 0.51 - 1.0 = Land
enum class TileType : u8 {
    Water = 0,
    Land = 1
};

struct Tile {
    bool m_IsOccupied = false;

    u8 m_NeighbourMask = 0;

    TileType m_Type = TileType::Land;
    Vector2Int m_SpriteSheetIndex = 5;

    static const char *TileTypeToString(TileType type) {
        switch (type) {
            case TileType::Water:
                return "Water";

            case TileType::Land:
                return "Land";
        }

        return "none";
    }
};

// Stores only relevant Information needed for rendering a Tile
struct RenderTile {
    Rectangle m_SourceRect = {0, 0, 0, 0};
};
