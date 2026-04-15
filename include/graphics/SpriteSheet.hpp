#pragma once

#include <string>
#include <spdlog/spdlog.h>
#include <raylib.h>

#include "tenshiUtil/Types.h"
#include "tenshiUtil/math/Vector2Int.hpp"

class SpriteSheet {
public:
    SpriteSheet(u32 id, Texture2D* texture, u32 fWidth, u32 fHeight);
    ~SpriteSheet();

    // Constructs a Source Rect for a Frame in the Spritesheet
    // 0,0 to MAX,MAX
    Rectangle GetSourceRect(const Vector2Int frame) const;

    Texture2D* GetTexture() { return m_Texture;}

public:
    const u32 m_Id;

private:
    Texture2D* m_Texture = nullptr;
    u32 m_fWidth = 16;
    u32 m_fHeight = 16;
    u32 m_framesPerRow = 0;
    u32 m_framesPerCol = 0;
};