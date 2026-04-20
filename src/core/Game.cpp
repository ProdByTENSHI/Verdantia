#include "core/Game.hpp"

#include <iostream>

#include "globals/Globals.hpp"

#include <raylib.h>
#include "tenshiUtil/math/Random.h"
#include "globals/Events.hpp"

Island* island = nullptr;

void GenerateIsland()
{
    g_WorldGenerator->SetSeed(Random::GetInt(42, 1337));
    island = g_WorldGenerator->GenerateIsland({24, 24}, {15.0f, 15.0f});
}

Game::Game()
{
    InitWindow(g_WindowWidth, g_WindowHeight, "Verdantia");
    SetTargetFPS(60);

    // ToggleFullscreen();
    // g_WindowWidth = 1920;
    // g_WindowHeight = 1080;

    g_RscManager = std::make_unique<RscManager>();
    g_RscManager->LoadAssets();
    g_EntityManager = std::make_unique<EntityManager>();
    g_WorldGenerator = std::make_unique<WorldGenerator>(1337);
    g_MasterRenderer = std::make_unique<MasterRenderer>();
    g_Camera = std::make_unique<VerdantiaCamera>();

    // == DEBUG
    g_WorldGenerator->GenerateWorld();
    GenerateIsland();
    // ========

    m_Player = g_EntityManager->CreateEntity<Player>();
    m_Player->m_Position = {
        (island->m_Size.x * 16.0f) * 0.5f + island->m_Position.x,
        (island->m_Size.y * 16.0f) * 0.5f + island->m_Position.y
    };

    m_IsRunning = true;
}

Game::~Game()
{
    CloseWindow();

    spdlog::info("Closed Game");
}

void Game::Update()
{
    while (m_IsRunning)
    {
        // -- Animation Tick
        if (m_TimeSinceLastAnimTick >= TIME_BETWEEN_ANIM_TICKS)
        {
            m_TimeSinceLastAnimTick = 0.0f;
            OnAnimTick.Dispatch();
        }
        else
        {
            m_TimeSinceLastAnimTick += GetFrameTime();
        }

        OnUpdate.Dispatch();
        m_Player->Update();

        // Update Camera after Entity Updates
        g_Camera->Update(m_Player->m_Position);

        Render();

        g_EntityManager->AfterEntitiesFinished();

        if (WindowShouldClose())
        {
            m_IsRunning = false;
        }
    }
}

void Game::Render()
{
    g_MasterRenderer->Render();
}
