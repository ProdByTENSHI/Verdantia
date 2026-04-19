#include "player/PlayerState.hpp"

#include "globals/Globals.hpp"

PlayerState::PlayerState(PlayerStates state)
    : m_State(state)
{
}

void PlayerState::SetFacingDirection(Vector2Int dir)
{
    m_FacingDirection = dir;
}

Animation* PlayerState::GetAnimation()
{
    if (m_FacingDirection == DOWN_DIR)
    {
        return g_RscManager->GetAnimation(m_DownAnimId);
    }
    else if (m_FacingDirection == UP_DIR)
    {
        return g_RscManager->GetAnimation(m_UpAnimId);
    }
    else if (m_FacingDirection == RIGHT_DIR)
    {
        return g_RscManager->GetAnimation(m_RightAnimId);
    }
    else if (m_FacingDirection == LEFT_DIR)
    {
        return g_RscManager->GetAnimation(m_LeftAnimId);
    }

    return g_RscManager->GetAnimation(Animations::PlayerIdleDown);
}

