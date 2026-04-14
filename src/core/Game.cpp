#include "core/Game.hpp"

#include <iostream>

#include "globals/Globals.hpp"

#include <raylib.h>
#include "tenshiUtil/math/Random.h"
#include "globals/Events.hpp"

SpriteSheet *grasslandTexture;
SpriteSheet *waterTexture;

Island* island = nullptr;

void GenerateIsland() {
    g_WorldGenerator->SetSeed(Random::GetInt(-25255, 35834));
    island = g_WorldGenerator->GenerateIsland({32,32}, {15,15});
}

Game::Game() {
    InitWindow(g_WindowWidth, g_WindowHeight, "Verdantia");
    SetTargetFPS(60);
    // ToggleFullscreen();

    g_RscManager = std::make_unique<RscManager>();
    g_WorldGenerator = std::make_unique<WorldGenerator>(1337);
    g_MasterRenderer = std::make_unique<MasterRenderer>();

    // == DEBUG
    g_WorldGenerator->GenerateWorld();
    GenerateIsland();

    grasslandTexture = g_RscManager->GetSpriteSheet(TextureType::GroundTile, "Grass_Tiles.png");
    waterTexture = g_RscManager->GetSpriteSheet(TextureType::GroundTile, "Water.png");

    g_Camera.zoom = 2.0f;
    g_Camera.target = {g_WindowWidth * 0.5f, g_WindowHeight * 0.5f};
    g_Camera.offset = {g_WindowWidth * 0.5f, g_WindowHeight * 0.5f};
    // ========

    std::cout << TOP_RIGHT_CORNER_INDEX.x << " " << TOP_RIGHT_CORNER_INDEX.y << std::endl;

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

        if (IsKeyDown(KEY_W)) {
            g_Camera.target.y -= 3.0f;
        } else if (IsKeyDown(KEY_S)) {
            g_Camera.target.y += 3.0f;
        }
        if (IsKeyDown(KEY_A)) {
            g_Camera.target.x -= 3.0f;
        } else if (IsKeyDown(KEY_D)) {
            g_Camera.target.x += 3.0f;
        }

        if (IsKeyPressed(KEY_Q)) {
            g_Camera.zoom += 0.5f;
        } else if (IsKeyPressed(KEY_E)) {
            g_Camera.zoom -= 0.5f;

        }

        OnUpdate.Dispatch();

        Render();

        if (WindowShouldClose()) {
            m_IsRunning = false;
        }
    }
}

void Game::Render() {
    g_MasterRenderer->Render();
}
