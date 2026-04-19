#include "player/Player.hpp"

#include "raymath.h"
#include "globals/Globals.hpp"

Player::Player(u32 id, const std::string& name) : Entity(id, "Player")
{
    // -- Init States
    m_IdleState = new PlayerIdleState();

    SetState(PlayerStates::Idle);

    UpdateHandler.SetFunction([this]()
    {
        Update();
    });
    OnUpdate += UpdateHandler;

    RenderHandler.SetFunction([this]()
    {
        Render();
    });
    OnRender += RenderHandler;

    m_RenderLayer = RenderLayer::Entities;
}

Player::~Player()
{
    OnUpdate -= UpdateHandler;
    OnRender -= RenderHandler;
}

void Player::Update()
{
    m_Position += m_MovementVector * GetFrameTime();

    m_CurrentAnimation->Update();
}

RenderCommand Player::CreateRenderCommand()
{
    RenderCommand _cmd = m_CurrentAnimation->GetRenderCommand();;

    _cmd.m_Position = m_Position;

    return _cmd;
}

void Player::Render()
{
    g_MasterRenderer->PushRenderCommand(m_RenderLayer, CreateRenderCommand());
}

void Player::SetFacingDirection(Vector2Int direction)
{
    m_FacingDirection = direction;
    m_CurrentState->SetFacingDirection(direction);
    m_CurrentAnimation = m_CurrentState->GetAnimation();
}

void Player::SetState(PlayerStates state)
{
    if (m_CurrentState != nullptr && state == m_CurrentState->m_State)
        return;

    PlayerState* _lastState = nullptr;
    if (m_CurrentState != nullptr)
        _lastState = m_CurrentState;

    switch (state)
    {
    case PlayerStates::Idle:
        m_CurrentState = m_IdleState;
        break;
    }

    if (_lastState != nullptr)
        _lastState->OnExit(*m_CurrentState);
    m_CurrentState->OnEntry(*_lastState);

    m_CurrentAnimation = m_CurrentState->GetAnimation();
}
