#pragma once

#include "player/PlayerState.hpp"

class PlayerIdleState : public virtual PlayerState
{
public:
    void OnEntry(PlayerState& lastState) override;
    void OnUpdate() override;
    void OnExit(PlayerState& nextState) override;
};
