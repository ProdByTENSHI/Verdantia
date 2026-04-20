#include "player/PlayerWalkState.hpp"

#include "globals/Globals.hpp"

PlayerWalkState::PlayerWalkState(PlayerStates state)
    : PlayerState(state)
{
    m_DownAnimId = Animations::PlayerWalkDown;
    m_UpAnimId = Animations::PlayerWalkUp;
    m_RightAnimId = Animations::PlayerWalkRight;
    m_LeftAnimId = Animations::PlayerWalkLeft;
}

PlayerWalkState::~PlayerWalkState()
{
}

void PlayerWalkState::OnEntry(PlayerState& lastState)
{
}

void PlayerWalkState::OnUpdate()
{
}

void PlayerWalkState::OnExit(PlayerState& nextState)
{
}

Animation* PlayerWalkState::GetAnimation()
{
    Animation* anim = PlayerState::GetAnimation();
    return anim;
}
