#include "core/Game.hpp"
#include "globals/Globals.hpp"

#include <raylib.h>
#include "tenshiUtil/math/Random.h"

Texture2D* grasslandTexture;
Texture2D* waterTexture;

Rectangle waterTextureSource;
Rectangle grasslandTextureSource;

void GenerateIsland() {
    g_WorldGenerator->SetSeed(Random::GetInt(-25255, 35834));
    g_WorldGenerator->GenerateIsland({5, 5}, {32, 32}, 3.0f);
}

Game::Game() {
    InitWindow(g_WindowWidth, g_WindowHeight, "Verdantia");
    SetTargetFPS(60);
    // ToggleFullscreen();

    grasslandTextureSource = {0, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    waterTextureSource = {0, 0, TILE_SIZE, TILE_SIZE};

    g_RscManager = std::make_unique<RscManager>();
    g_WorldGenerator = std::make_unique<WorldGenerator>(1337);

    // == DEBUG
    g_WorldGenerator->GenerateWorld();
    GenerateIsland();

    grasslandTexture = g_RscManager->GetTexture(TextureType::GroundTile, "Grass_Tiles.png");
    waterTexture = g_RscManager->GetTexture(TextureType::GroundTile, "Water.png");

    g_Camera.zoom = 1.0f;
    g_Camera.target = {g_WindowWidth * 0.5f, g_WindowHeight * 0.5f};
    g_Camera.offset = {g_WindowWidth * 0.5f, g_WindowHeight * 0.5f};
    // ========

    m_IsRunning = true;
}

Game::~Game() {
    CloseWindow();

    spdlog::info("Closed Game");
}

void Game::Update() {
    while (m_IsRunning) {
        if (IsKeyPressed(KEY_SPACE)) {
            GenerateIsland();
        }

        if (IsKeyPressed(KEY_W)) {
            g_Camera.zoom += 0.15f;
            spdlog::info("Zoom: {}", g_Camera.zoom);
        } else if (IsKeyPressed(KEY_S)) {
            g_Camera.zoom -= 0.15f;
            spdlog::info("Zoom: {}", g_Camera.zoom);
        }

        Render();

        if (WindowShouldClose()) {
            m_IsRunning = false;
        }
    }
}

void Game::Render() {
    BeginDrawing();
    BeginMode2D(g_Camera);

    ClearBackground(RAYWHITE);
    for (i32 x = 0; x < g_WindowWidth; x++) {
        for (i32 y = 0; y < g_WindowHeight; y++) {
            switch (g_WorldGenerator->m_Tiles[x][y].m_Type) {
                case TileType::Water:
                    DrawTextureRec(*waterTexture, waterTextureSource, {
                                       (f32) x * TILE_SIZE,
                                       (f32) y * TILE_SIZE
                                   }, WHITE);
                    break;

                case TileType::Grassland:
                    DrawTextureRec(*grasslandTexture, grasslandTextureSource, {
                                       (f32) x * TILE_SIZE,
                                       (f32) y * TILE_SIZE
                                   }, WHITE);
                    break;
            }
        }
    }

    EndMode2D();
    EndDrawing();
}
