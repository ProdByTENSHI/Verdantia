#pragma once

#include "entities/Entity.hpp"
#include "globals/Events.hpp"
#include "graphics/SpriteSheet.hpp"
#include "math/Vector2Int.hpp"
#include "graphics/Animation.hpp"
#include "player/PlayerIdleState.hpp"
#include "player/PlayerWalkState.hpp"


class Player : virtual public Entity
{
public:
    // You can leave name empty
    Player(u32 id, const std::string& name = "");

    ~Player();

    void Update() override;

    RenderCommand CreateRenderCommand() override;

    void Render() override;

    void SetFacingDirection(Vector2Int direction);
    void SetState(PlayerStates state);

private:
    f32 m_WalkingSpeed = 25.0f;
    f32 m_RunningSpeed = m_WalkingSpeed * 1.75;
    f32 m_TimeBetweenActions = 0.6f;

    Vector2Int m_FacingDirection = DOWN_DIR;

    Vector2 m_MovementVector = {0.0f, 0.0f};

    PlayerState* m_CurrentState = nullptr;
    PlayerIdleState* m_IdleState = nullptr;
    PlayerWalkState* m_WalkState = nullptr;

    Animation* m_CurrentAnimation = nullptr;

private:
    EventHandler<> UpdateHandler;
    EventHandler<> RenderHandler;
};
