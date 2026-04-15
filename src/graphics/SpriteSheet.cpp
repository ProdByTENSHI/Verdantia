#include "graphics/SpriteSheet.hpp"

SpriteSheet::SpriteSheet(u32 id, Texture2D *texture, u32 fWidth, u32 fHeight)
    : m_Id(id), m_Texture(texture), m_fWidth(fWidth), m_fHeight(fHeight) {
    m_framesPerRow = texture->width / fWidth;
    m_framesPerCol = texture->height / fHeight;
}

SpriteSheet::~SpriteSheet() {
}

Rectangle SpriteSheet::GetSourceRect(const Vector2Int frame) const {
    Rectangle _rect = {
        (f32) frame.x * m_fWidth, (f32) frame.y * m_fHeight,
        (f32) m_fWidth, (f32) m_fHeight
    };

    return _rect;
}
