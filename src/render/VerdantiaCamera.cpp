#include "render/VerdantiaCamera.hpp"

#include "globals/Globals.hpp"

VerdantiaCamera::VerdantiaCamera() {
    m_Camera.offset = {g_WindowWidth * 0.5f, g_WindowHeight * 0.5f};
    m_Camera.zoom = 3.0f;
}

VerdantiaCamera::~VerdantiaCamera() {
}

void VerdantiaCamera::Update(Vector2 target) {
    m_Camera.target = target;
}
