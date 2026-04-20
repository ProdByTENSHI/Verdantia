#include "world/Island.hpp"
#include <spdlog/spdlog.h>

#include "raylib.h"
#include "globals/Globals.hpp"

Island::Island(Tile** tiles, Vector2Int size, Vector2 pos) : m_Size(size), m_Position(pos)
{
    m_Tiles = tiles;
    m_RenderTiles = new RenderTile*[size.x];
    for (i32 x = 0; x < m_Size.x; x++)
    {
        m_RenderTiles[x] = new RenderTile[size.y];
        for (i32 y = 0; y < m_Size.y; y++)
        {
            Tile tile = tiles[x][y];
            RenderTile renderTile;

            renderTile.m_SpriteSheetIndex = tile.m_SpriteSheetIndex;
            renderTile.m_SourceRect = g_RscManager->GetSpritesheet(tile.m_SpriteSheetIndex)->GetSourceRect(
                tile.m_TileIndex);

            if (tile.m_Type != TileType::Water)
                m_RenderTiles[x][y] = renderTile;
        }
    }


    RenderHandler.SetFunction([this]()
    {
        this->Render();
    });
    OnRender += RenderHandler;
}

Island::~Island()
{
    OnRender -= RenderHandler;
}

void Island::Render()
{
    RenderCommand _cmd;

    for (i32 x = 0; x < m_Size.x; x++)
    {
        for (i32 y = 0; y < m_Size.y; y++)
        {
            RenderTile& tile = m_RenderTiles[x][y];

            _cmd.m_SrcRect = tile.m_SourceRect;
            _cmd.m_Position = Vector2(x * m_Position.x, y * m_Position.y);
            _cmd.m_TextureId = g_RscManager->GetSpritesheet(tile.m_SpriteSheetIndex)->GetTexture();

            g_MasterRenderer->PushRenderCommand(RenderLayer::Ground, _cmd);
        }
    }
    for (auto& e : m_StaticEntities)
    {
        g_MasterRenderer->PushRenderCommand(RenderLayer::Entities,
                                            e.second->CreateRenderCommand());
    }
}

void Island::AddStaticEntity(Entity* entity, Vector2Int tilePos)
{
    if (IsTileOccupied(tilePos))
    {
        spdlog::error("Could not add static Entity to Island since the Tile {} {} is occupied",
                      tilePos.x, tilePos.y);
        return;
    }

    m_StaticEntities.insert({tilePos, entity});
    m_Tiles[tilePos.x][tilePos.y].m_IsOccupied = true;
}

Entity* Island::GetStaticEntity(Vector2Int tilePos)
{
    if (m_StaticEntities.find(tilePos) != m_StaticEntities.end())
        return m_StaticEntities[tilePos];

    return nullptr;
}

bool Island::IsTileOccupied(Vector2Int tilePos) const
{
    if (tilePos.x < 0 || tilePos.x >= m_Size.x || tilePos.y < 0 || tilePos.y >= m_Size.y)
    {
        spdlog::warn("IsTileOccupied was passed an invalid Tile Pos {} {}", tilePos.x, tilePos.y);
        return false;
    }

    return m_Tiles[tilePos.y][tilePos.x].m_IsOccupied;
}

Tile& Island::GetTile(Vector2Int tile)
{
    if (tile.x < 0 || tile.x > m_Size.x || tile.y < 0 || tile.y > m_Size.y)
    {
        spdlog::error("Could not get tile because of invalid Index {} {}",
                      tile.x, tile.y);
        exit(-1);
    }

    return m_Tiles[tile.y][tile.x];
}

RenderTile& Island::GetRenderTile(Vector2Int tile)
{
    if (tile.x < 0 || tile.x > m_Size.x || tile.y < 0 || tile.y > m_Size.y)
    {
        spdlog::error("Could not get render tile because of invalid Index {} {}",
                      tile.x, tile.y);
        exit(-1);
    }

    return m_RenderTiles[tile.y][tile.x];
}
