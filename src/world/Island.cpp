#include "world/Island.hpp"
#include <spdlog/spdlog.h>

#include "raylib.h"
#include "globals/Globals.hpp"

Island::Island(Tile **tiles, Vector2Int size, Vector2 pos) : m_Size(size), m_Position(pos) {
    m_TilesSprite = g_RscManager->GetSpriteSheet(TextureType::GroundTile, "Grass_Tiles.png");
    m_Tiles = tiles;
    m_RenderTiles = new RenderTile *[size.y];
    for (i32 x = 0; x < m_Size.x; x++) {
        m_RenderTiles[x] = new RenderTile[size.x];
        for (i32 y = 0; y < m_Size.y; y++) {
            Tile tile = tiles[x][y];
            RenderTile renderTile;

            renderTile.m_SourceRect = m_TilesSprite->GetSourceRect(tile.m_SpriteSheetIndex);

            m_RenderTiles[x][y] = renderTile;
        }
    }


    RenderHandler.SetFunction([this]() {
        this->Render();
    });
    OnRender += RenderHandler;
}

Island::~Island() {
    OnRender -= RenderHandler;
}

void Island::Render() {
    for (i32 x = 0; x < m_Size.x; x++) {
        for (i32 y = 0; y < m_Size.y; y++) {
            RenderTile &tile = m_RenderTiles[y][x];
            DrawTextureRec(*m_TilesSprite->GetTexture(), tile.m_SourceRect,
                           {m_Position.x + (x * TILE_SIZE), m_Position.y + (y * TILE_SIZE)},
                           WHITE);

        }
    }
}

Tile &Island::GetTile(Vector2Int tile) {
    if (tile.x < 0 || tile.x > m_Size.x || tile.y < 0 || tile.y > m_Size.y) {
        spdlog::error("Could not get tile because of invalid Index {} {}",
                      tile.x, tile.y);
        exit(-1);
    }

    return m_Tiles[tile.y][tile.x];
}

RenderTile &Island::GetRenderTile(Vector2Int tile) {
    if (tile.x < 0 || tile.x > m_Size.x || tile.y < 0 || tile.y > m_Size.y) {
        spdlog::error("Could not get render tile because of invalid Index {} {}",
                      tile.x, tile.y);
        exit(-1);
    }

    return m_RenderTiles[tile.y][tile.x];
}
