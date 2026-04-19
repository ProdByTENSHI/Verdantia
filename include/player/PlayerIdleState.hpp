#pragma once

#include "player/PlayerState.hpp"

class PlayerIdleState : public virtual PlayerState
{
public:
    explicit PlayerIdleState(PlayerStates state = PlayerStates::Idle);
    ~PlayerIdleState() override;

    void OnEntry(PlayerState& lastState) override;
    void OnUpdate() override;
    void OnExit(PlayerState& nextState) override;

    Animation* GetAnimation() override;
};
