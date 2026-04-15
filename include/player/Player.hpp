#pragma once

#include "entities/Entity.hpp"
#include "globals/Events.hpp"
#include "graphics/SpriteSheet.hpp"
#include "math/Vector2Int.hpp"

// One Frame in the Characters Sheet is 48 by 48
constexpr u32 PLAYER_SPRITE_SIZE = 48;

// Define all States that the Player can be in
enum class PlayerState {
    Idle,
    Walking,
    Running,
    Use_Hoe,
    Use_Watercan,
    Use_Pickaxe
};

class Player : virtual public Entity {
public:
    // You can leave name empty
    Player(u32 id, const std::string& name = "");

    ~Player();

    void Update() override;

    RenderCommand CreateRenderCommand() override;

    void Render() override;

    void Move(Vector2 movement, PlayerState state = PlayerState::Walking);

    // Returns the Index into the Sprite Sheet for the current State
    Rectangle GetFrameRect() const;

    void SetState(PlayerState state);

private:
    f32 m_WalkingSpeed = 35.0f;
    f32 m_RunningSpeed = m_WalkingSpeed * 1.75;
    f32 m_TimeBetweenActions = 0.6f;

    // 1, 0 -> Right
    // -1, 0 -> Left
    // 0, -1 -> Top
    // 0, 1 -> Bottom
    const Vector2Int RIGHT_DIR = Vector2Int(1, 0);
    const Vector2Int LEFT_DIR = Vector2Int(-1, 0);
    const Vector2Int UP_DIR = Vector2Int(0, -1);
    const Vector2Int DOWN_DIR = Vector2Int(0, 1);
    Vector2Int m_FacingDirection = DOWN_DIR;

    // Down Sprites for these Actions
    const u32 IDLE_SPRITE_INDEX = 0;
    const u32 WALKING_SPRITE_INDEX = IDLE_SPRITE_INDEX + 4;
    const u32 RUNNING_SPRITE_INDEX = WALKING_SPRITE_INDEX + 4;
    const u32 USE_HOE_SPRITE_INDEX = RUNNING_SPRITE_INDEX + 4;
    const u32 USE_WATERCAN_SPRITE_INDEX = USE_HOE_SPRITE_INDEX + 4;
    const u32 USE_PICKAXE_SPRITE_INDEX = USE_WATERCAN_SPRITE_INDEX + 4;

    Vector2 m_MovementVector = {0.0f, 0.0f};

    PlayerState m_State = PlayerState::Idle;

    // From 0 to 8
    const u32 MAX_ANIM_FRAME = 8;
    u32 m_CurrentFrame = 0;
    bool m_ShouldUpdateFrame = false;
    Rectangle m_SourceRect
            = {0, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE};
    SpriteSheet* m_SpriteSheet;
    Texture2D m_SpriteSheetTexture;

    EventHandler<> RenderEventHandler;
    EventHandler<> AnimationUpdateEventHandler;
};
