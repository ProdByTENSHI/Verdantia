#pragma once

#include "globals/Constants.hpp"

// Tile Values
// 0.0 - 0.5 = Water
// 0.51 - 1.0 = Grassland
enum class TileType : u8 {
    Water = 0,
    Grassland = 1
};

struct Tile {
    bool m_IsOccupied = false;
    TileType m_Type = TileType::Grassland;

    static const char *TileTypeToString(TileType type) {
        switch (type) {
            case TileType::Water:
                return "Water";

            case TileType::Grassland:
                return "Grassland";
        }

        return "none";
    }
};
