#pragma once

#include <raylib.h>
#include "globals/Constants.hpp"

// Holds all Data for Rendering something to the Screen
struct RenderCommand {
    u32 m_SpriteSheetId = 0;
    Rectangle m_SourceRect = {0, 0, 0, 0};
    Vector2 m_Position  = {0, 0};
    TextureType m_TextureType;

    // Used for std:: algorithms
    bool operator<(const RenderCommand &other) const noexcept {
        return m_SpriteSheetId < other.m_SpriteSheetId;
    }

    RenderCommand& operator=(const RenderCommand& rhs) {
        m_SpriteSheetId = rhs.m_SpriteSheetId;
        m_SourceRect = rhs.m_SourceRect;
        m_Position  = rhs.m_Position;
        m_TextureType = rhs.m_TextureType;

        return *this;
    }
};