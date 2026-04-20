#pragma once

#include "world/Tile.hpp"
#include "tenshiUtil/math/Vector2Int.hpp"

#include <raylib.h>

#include "entities/Entity.hpp"
#include "graphics/SpriteSheet.hpp"
#include "globals/Events.hpp"

class Island
{
public:
    Island(Tile** tiles, Vector2Int size, Vector2 pos);

    ~Island();

    void Render();

    void AddStaticEntity(Entity* entity, Vector2Int tilePos);
    Entity* GetStaticEntity(Vector2Int tilePos);
    bool IsTileOccupied(Vector2Int tilePos) const;

    Tile& GetTile(Vector2Int tile);

    RenderTile& GetRenderTile(Vector2Int tile);

private:
    Tile** m_Tiles;
    RenderTile** m_RenderTiles;
    Vector2Int m_Size = {0, 0};
    Vector2 m_Position = {0, 0};

    // Holds Static Entities like Trees, Stones, etc
    std::unordered_map<Vector2Int, Entity*> m_StaticEntities;

    EventHandler<> RenderHandler;
};
