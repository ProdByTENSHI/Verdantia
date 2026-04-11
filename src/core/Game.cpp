#include "core/Game.hpp"
#include "globals/Globals.hpp"

#include <raylib.h>

Game::Game() {
    InitWindow(g_WindowWidth, g_WindowHeight, "Verdantia");

    m_IsRunning = true;
}

Game::~Game() {
    
}

void Game::Update() {}

void Game::Render() {}