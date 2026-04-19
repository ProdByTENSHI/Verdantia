#pragma once
#include "tenshiUtil/Types.h"

#include <vector>

#include "raylib.h"
#include "render/RenderCommand.hpp"

struct Animation
{
    Animation(u32 spriteSheetId, f32 interval, std::vector<Rectangle> frames);
    ~Animation();

    RenderCommand GetRenderCommand() const;

    u32 m_SpriteSheetId = 0;
    f32 m_Interval = 0.1f;
    std::vector<Rectangle> m_Frames;
    u32 m_CurrentFrame = 0;

private:
    Texture2D m_Texture;
};
