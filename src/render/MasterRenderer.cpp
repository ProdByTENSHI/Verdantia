#include "render/MasterRenderer.hpp"
#include "globals/Globals.hpp"
#include "globals/Events.hpp"

MasterRenderer::MasterRenderer() {
}

MasterRenderer::~MasterRenderer() {
}

void MasterRenderer::Render() {
    BeginDrawing();
    BeginMode2D(g_Camera);

    OnRender.Dispatch();

    ClearBackground(RAYWHITE);

    EndMode2D();
    EndDrawing();
}
