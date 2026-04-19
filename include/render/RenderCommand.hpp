#pragma once

#include <raylib.h>
#include "globals/Constants.hpp"

// Holds all Data for Rendering something to the Screen
struct RenderCommand {
    u32 m_TextureId = 0;
    Rectangle m_SrcRect;    // Pass w and h of texture for whole tex
    Vector2 m_Position  = {0, 0};

    // Used for std:: algorithms
    bool operator<(const RenderCommand &other) const noexcept {
        return m_TextureId < other.m_TextureId;
    }

    RenderCommand& operator=(const RenderCommand& rhs) {
        m_TextureId = rhs.m_TextureId;
        m_SrcRect = rhs.m_SrcRect;
        m_Position  = rhs.m_Position;

        return *this;
    }
};