#include "player/Player.hpp"

#include "raymath.h"
#include "globals/Globals.hpp"

Player::Player(u32 id, const std::string& name) : Entity(id, "Player")
{
    // -- Init States
    m_IdleState = new PlayerIdleState();
    m_WalkState = new PlayerWalkState();

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

    m_Position = {32.0f * 16.0f, 32.0f * 16.0f};
}

Player::~Player()
{
    OnUpdate -= UpdateHandler;
    OnRender -= RenderHandler;
}

void Player::Update()
{
    if (IsKeyDown(KEY_W))
    {
        SetFacingDirection(UP_DIR);
        SetState(PlayerStates::Walking);
        m_MovementVector = Vector2(0.0f, -1.0f);
    }
    else if (IsKeyDown(KEY_S))
    {
        SetFacingDirection(DOWN_DIR);
        SetState(PlayerStates::Walking);
        m_MovementVector = Vector2(0.0f, +1.0f);
    }
    else if (IsKeyDown(KEY_D))
    {
        SetFacingDirection(RIGHT_DIR);
        SetState(PlayerStates::Walking);
        m_MovementVector = Vector2(1.0f, 0.0f);
    }
    else if (IsKeyDown(KEY_A))
    {
        SetFacingDirection(LEFT_DIR);
        SetState(PlayerStates::Walking);
        m_MovementVector = Vector2(-1.0f, 0.0f);
    }

    if (IsKeyReleased(KEY_W))
    {
        SetState(PlayerStates::Idle);
        m_MovementVector = Vector2(0.0f, 0.0f);
    }
    else if (IsKeyReleased(KEY_S))
    {
        SetState(PlayerStates::Idle);
        m_MovementVector = Vector2(0.0f, 0.0f);
    }
    else if (IsKeyReleased(KEY_D))
    {
        SetState(PlayerStates::Idle);
        m_MovementVector = Vector2(0.0f, 0.0f);
    }
    else if (IsKeyReleased(KEY_A))
    {
        SetState(PlayerStates::Idle);
        m_MovementVector = Vector2(0.0f, 0.0f);
    }

    m_Position += m_MovementVector * GetFrameTime() * m_WalkingSpeed;

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

    case PlayerStates::Walking:
        m_CurrentState = m_WalkState;
        break;
    }

    if (_lastState != nullptr)
        _lastState->OnExit(*m_CurrentState);
    m_CurrentState->OnEntry(*_lastState);

    m_CurrentAnimation = m_CurrentState->GetAnimation();
}
