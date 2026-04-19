#include "player/Player.hpp"

#include "raymath.h"
#include "globals/Globals.hpp"

Player::Player(u32 id, const std::string &name) : Entity(id, "Player") {
    SetState(PlayerState::Walking);
}

Player::~Player() {
}

void Player::Update() {
    // -- Temporary Movement
    PlayerState _movementState = PlayerState::Walking;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        _movementState = PlayerState::Running;
    } else if (IsKeyReleased(KEY_LEFT_SHIFT)) {
        _movementState = PlayerState::Walking;
    }

    if (IsKeyDown(KEY_W)) {
        Move((Vector2) UP_DIR, _movementState);
    } else if (IsKeyDown(KEY_S)) {
        Move((Vector2) DOWN_DIR, _movementState);
    }
    if (IsKeyDown(KEY_A)) {
        Move((Vector2) LEFT_DIR, _movementState);
    } else if (IsKeyDown(KEY_D)) {
        Move((Vector2) RIGHT_DIR, _movementState);
    }

    if (IsKeyReleased(KEY_W)) {
        SetState(PlayerState::Idle);
        m_MovementVector = {0.0f, 0.0f};
    } else if (IsKeyReleased(KEY_S)) {
        SetState(PlayerState::Idle);
        m_MovementVector = {0.0f, 0.0f};
    }
    if (IsKeyReleased(KEY_A)) {
        SetState(PlayerState::Idle);
        m_MovementVector = {0.0f, 0.0f};
    } else if (IsKeyReleased(KEY_D)) {
        SetState(PlayerState::Idle);
        m_MovementVector = {0.0f, 0.0f};
    }

    m_Position += m_MovementVector * GetFrameTime();
}

void Player::Move(Vector2 movement, PlayerState state) {
    if (m_State != state)
        SetState(state);

    m_MovementVector = movement;
    Vector2Normalize(m_MovementVector);

    m_FacingDirection.x = (u32)m_MovementVector.x;
    m_FacingDirection.y = (u32)m_MovementVector.y;

    if (m_State == PlayerState::Walking) {
        m_MovementVector *= m_WalkingSpeed;
    } else if (m_State == PlayerState::Running) {
        m_MovementVector *= m_RunningSpeed;
    }

}

RenderCommand Player::CreateRenderCommand() {
    RenderCommand _cmd;

    return _cmd;
}

void Player::Render() {
    g_MasterRenderer->PushRenderCommand(m_RenderLayer, CreateRenderCommand());
}

void Player::SetState(PlayerState state) {
    m_State = state;
}
