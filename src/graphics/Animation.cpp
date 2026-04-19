#include "graphics/Animation.hpp"

#include "globals/Globals.hpp"

Animation::Animation(u32 spriteSheetId, f32 interval, std::vector<Rectangle> frames)
    : m_SpriteSheetId(spriteSheetId), m_Interval(interval), m_Frames(frames)
{
    m_TextureId = g_RscManager->GetSpritesheet(spriteSheetId)->GetTexture();
}

Animation::~Animation()
{
}

RenderCommand Animation::GetRenderCommand() const
{
    RenderCommand _cmd;

    Rectangle _frame = m_Frames[m_CurrentFrame];

    _cmd.m_TextureId = m_TextureId;
    _cmd.m_SrcRect = {
        _frame.x * _frame.width, _frame.y * _frame.height,
        _frame.width, _frame.height
    };

    return _cmd;
}

void Animation::Update()
{
    if (m_TimeSinceLastFrame >= m_Interval)
    {
        m_TimeSinceLastFrame = 0.0f;

        if (m_CurrentFrame >= m_Frames.size() - 1)
            m_CurrentFrame = 0;
        else
        {
            ++m_CurrentFrame;
        }
    }
    else
    {
        m_TimeSinceLastFrame += GetFrameTime();
    }
}
