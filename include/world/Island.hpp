#pragma once

#include "world/Tile.hpp"
#include "tenshiUtil/math/Vector2Int.hpp"

#include <raylib.h>

#include "graphics/SpriteSheet.hpp"
#include "globals/Events.hpp"

class Island {
public:
    Island(Tile **tiles, Vector2Int size, Vector2 pos);

    ~Island();

    void Render();

    Tile &GetTile(Vector2Int tile);

    RenderTile &GetRenderTile(Vector2Int tile);

private:
    Tile **m_Tiles;
    RenderTile **m_RenderTiles;
    Vector2Int m_Size = {0, 0};
    Vector2 m_Position = {0, 0};
    SpriteSheet *m_TilesSprite = nullptr;

    EventHandler<> RenderHandler;
};
