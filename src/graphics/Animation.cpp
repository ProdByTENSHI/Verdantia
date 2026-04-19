#include "graphics/Animation.hpp"

#include "globals/Globals.hpp"

Animation::Animation(u32 spriteSheetId, f32 interval, std::vector<Rectangle> frames)
    : m_SpriteSheetId(spriteSheetId), m_Interval(interval), m_Frames(frames)
{
    m_Texture = *g_RscManager->GetTexture(
        g_RscManager->GetSpriteSheetById(m_SpriteSheetId)->GetTexture());
}

Animation::~Animation()
{
}

RenderCommand Animation::GetRenderCommand() const
{
    RenderCommand _cmd;

    _cmd.m_TextureId = m_Texture.id;
    _cmd.m_SrcRect = m_Frames[m_CurrentFrame];

    return _cmd;
}
