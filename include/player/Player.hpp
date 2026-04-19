#pragma once

#include "entities/Entity.hpp"
#include "globals/Events.hpp"
#include "graphics/SpriteSheet.hpp"
#include "math/Vector2Int.hpp"
#include "graphics/Animation.hpp"

// Define all States that the Player can be in
enum class PlayerState
{
    Idle,
    Walking,
    Running,
    Use_Hoe,
    Use_Watercan,
    Use_Pickaxe
};

class Player : virtual public Entity
{
public:
    // You can leave name empty
    Player(u32 id, const std::string& name = "");

    ~Player();

    void Update() override;

    RenderCommand CreateRenderCommand() override;

    void Render() override;

    void Move(Vector2 movement, PlayerState state = PlayerState::Walking);

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

    Vector2 m_MovementVector = {0.0f, 0.0f};

    PlayerState m_State = PlayerState::Idle;
};
