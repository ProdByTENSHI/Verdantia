#pragma once

#include "player/PlayerState.hpp"

class PlayerWalkState : public virtual PlayerState
{
public:
    explicit PlayerWalkState(PlayerStates state = PlayerStates::Walking);
    ~PlayerWalkState() override;

    void OnEntry(PlayerState& lastState) override;
    void OnUpdate() override;
    void OnExit(PlayerState& nextState) override;

    Animation* GetAnimation() override;
};
