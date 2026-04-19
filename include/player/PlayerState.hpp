#pragma once

#include "graphics/Animation.hpp"
#include "globals/Constants.hpp"

// Define all States that the Player can be in
enum class PlayerStates
{
    Idle,
    Walking,
    Running,
    Use_Hoe,
    Use_Watercan,
    Use_Pickaxe
};

class PlayerState
{
public:
    PlayerState(PlayerStates state);

    virtual ~PlayerState()
    {
    }

    virtual void OnEntry(PlayerState& lastState) = 0;
    virtual void OnUpdate() = 0;
    virtual void OnExit(PlayerState& nextState) = 0;

    virtual void SetFacingDirection(Vector2Int dir);
    virtual Animation* GetAnimation();

    const PlayerStates m_State;
    Vector2Int m_FacingDirection = DOWN_DIR;

protected:
    u32 m_DownAnimId = 0;
    u32 m_UpAnimId = 0;
    u32 m_RightAnimId = 0;
    u32 m_LeftAnimId = 0;
};
