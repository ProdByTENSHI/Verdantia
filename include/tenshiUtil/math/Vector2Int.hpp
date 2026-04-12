#pragma once

#include "tenshiUtil/Types.h"

#include <functional>

struct Vector2Int {
    i32 x = 0;
    i32 y = 0;

    Vector2Int(i32 val) : x(val), y(val) {}
    Vector2Int(u32 x, u32 y) : x(x), y(y) {   }

    bool operator ==(const Vector2Int &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator !=(const Vector2Int &rhs) const {
        return x != rhs.x || y != rhs.y;
    }
};

template<>
struct std::hash<Vector2Int> {
    std::size_t operator()(const Vector2Int &coord) const {
        return std::hash<i32>()(coord.x) ^ (std::hash<i32>()(coord.y) << 1);
    }
};
