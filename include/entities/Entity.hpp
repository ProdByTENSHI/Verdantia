#pragma once

#include "tenshiUtil/Types.h"

#include <raylib.h>

// Base Class for all Entities
class Entity {
public:
    explicit Entity(u32 id) : m_Id(id) {}

    virtual ~Entity() = 0;

    virtual void Update() = 0;
    virtual void Render() = 0;

public:
    const u32 m_Id;
    static u32 s_IdCounter;

    Vector2 m_Position = {0.0f, 0.0f};
};