#pragma once

#include "tenshiUtil/eventsystem/EventSystem.h"

inline Event<> OnUpdate;
inline Event<> OnRender;

// Gets called when Sprite Sheet Anims should be updated
inline Event<> OnAnimTick;