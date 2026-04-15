#pragma once

#include "player/Player.hpp"

class Game {
public:
    Game();
    ~Game();

    void Update();
    void Render();

private:
    Player* m_Player;

    f32 m_TimeSinceLastAnimTick = 0.0f;

    bool m_IsRunning = false;
};