#pragma once

class PlayerState
{
public:
    virtual ~PlayerState()
    {
    }

    virtual void OnEntry(PlayerState& lastState) = 0;
    virtual void OnUpdate() = 0;
    virtual void OnExit(PlayerState& nextState) = 0;
};
