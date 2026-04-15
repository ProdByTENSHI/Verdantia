#include "player/Player.hpp"

#include "raymath.h"
#include "globals/Globals.hpp"

Player::Player(u32 id, const std::string &name) : Entity(id, "Player") {
    m_SpriteSheet = g_RscManager->LoadSpriteSheet(TextureType::Player, "Character.png");
    m_SpriteSheetTexture = *m_SpriteSheet->GetTexture();

    AnimationUpdateEventHandler.SetFunction([this]() {
        m_ShouldUpdateFrame = true;
    });

    RenderEventHandler.SetFunction([this]() {
        Render();
    });

    OnAnimTick += AnimationUpdateEventHandler;
    OnRender += RenderEventHandler;

    SetState(PlayerState::Walking);
}

Player::~Player() {
    OnAnimTick -= AnimationUpdateEventHandler;
    OnRender -= RenderEventHandler;
}

void Player::Update() {
    // -- Update Frame
    if (m_ShouldUpdateFrame) {
        m_SourceRect = GetFrameRect();

        if (m_CurrentFrame < MAX_ANIM_FRAME) {
            ++m_CurrentFrame;
        } else {
            m_CurrentFrame = 0;
        }

        m_ShouldUpdateFrame = false;
    }

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
    RenderCommand _command;

    _command.m_SpriteSheetId = m_SpriteSheet->m_Id;
    _command.m_SourceRect = m_SourceRect;
    _command.m_Position = m_Position;
    _command.m_TextureType = TextureType::Player;

    return _command;
}

void Player::Render() {
    g_MasterRenderer->PushRenderCommand(m_RenderLayer, CreateRenderCommand());
}

Rectangle Player::GetFrameRect() const {
    Rectangle _rect{0, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE};

    // Directions Order are same for all Moves: Down, Up, Right, Left
    // Use this to calculate correct direction Row
    u32 _dirOffsetFromAction = 0;
    if (m_FacingDirection == UP_DIR) {
        ++_dirOffsetFromAction;
    } else if (m_FacingDirection == RIGHT_DIR) {
        _dirOffsetFromAction += 2;
    } else if (m_FacingDirection == LEFT_DIR) {
        _dirOffsetFromAction += 3;
    }

    switch (m_State) {
        case PlayerState::Idle:
            _rect.y = IDLE_SPRITE_INDEX + _dirOffsetFromAction;
            break;

        case PlayerState::Walking:
            _rect.y = WALKING_SPRITE_INDEX + _dirOffsetFromAction;
            break;

        case PlayerState::Running:
            _rect.y = RUNNING_SPRITE_INDEX + _dirOffsetFromAction;
            break;

        case PlayerState::Use_Hoe:
            _rect.y = USE_HOE_SPRITE_INDEX + _dirOffsetFromAction;
            break;

        case PlayerState::Use_Watercan:
            _rect.y = USE_WATERCAN_SPRITE_INDEX + _dirOffsetFromAction;
            break;

        case PlayerState::Use_Pickaxe:
            _rect.y = USE_PICKAXE_SPRITE_INDEX + _dirOffsetFromAction;
            break;
    }

    _rect.x = m_CurrentFrame * PLAYER_SPRITE_SIZE;
    _rect.y = _rect.y * PLAYER_SPRITE_SIZE;

    return _rect;
}

void Player::SetState(PlayerState state) {
    m_State = state;
    m_CurrentFrame = 0;
    m_ShouldUpdateFrame = true;
}
