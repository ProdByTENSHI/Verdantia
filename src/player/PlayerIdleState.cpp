#include "player/PlayerIdleState.hpp"

#include "globals/Globals.hpp"

PlayerIdleState::PlayerIdleState(PlayerStates state)
    : PlayerState(state)
{
    m_DownAnimId = Animations::PlayerIdleDown;
    m_UpAnimId = Animations::PlayerIdleUp;
    m_RightAnimId = Animations::PlayerIdleRight;
    m_LeftAnimId = Animations::PlayerIdleLeft;
}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::OnEntry(PlayerState& lastState)
{
}

void PlayerIdleState::OnUpdate()
{
}

void PlayerIdleState::OnExit(PlayerState& nextState)
{
}

Animation* PlayerIdleState::GetAnimation()
{
    return PlayerState::GetAnimation();
}
