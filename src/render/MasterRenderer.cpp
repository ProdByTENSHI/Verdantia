#include "render/MasterRenderer.hpp"
#include "globals/Globals.hpp"
#include "globals/Events.hpp"

MasterRenderer::MasterRenderer() {
}

MasterRenderer::~MasterRenderer() {
}

void MasterRenderer::Render() {
    BeginDrawing();
    BeginMode2D(g_Camera->GetCamera());
    OnRender.Dispatch();

    StageRenderCmdBuffers();

    RenderCommand _cmd;
    for (i32 i = 0; i < m_GroundRenderCommands.size(); i++) {
        _cmd = m_GroundRenderCommands[i];

        DrawTextureRec(*g_RscManager->GetSpriteSheetById(_cmd.m_TextureType, _cmd.m_SpriteSheetId)->GetTexture(),
                       _cmd.m_SourceRect, _cmd.m_Position, WHITE);
    }

    for (i32 i = 0; i < m_EntityRenderCommands.size(); i++) {
        _cmd = m_EntityRenderCommands[i];

        DrawTextureRec(*g_RscManager->GetSpriteSheetById(_cmd.m_TextureType, _cmd.m_SpriteSheetId)->GetTexture(),
                       _cmd.m_SourceRect, _cmd.m_Position, WHITE);
    }

    DrawCircleV({(f32)g_WindowWidth / 2, (f32)g_WindowHeight / 2}, 10, BLACK);

    ClearBackground(RAYWHITE);

    EndMode2D();

    // -- RENDER UI HERE LATER

    EndDrawing();

    m_GroundRenderCommands.clear();
    m_EntityRenderCommands.clear();
}

void MasterRenderer::PushRenderCommand(RenderLayer layer, RenderCommand cmd) {
    GetCommandBufferByLayer(layer).push_back(cmd);
}

void MasterRenderer::StageRenderCmdBuffers() {
    // -- Sort Render Command Buffers
    std::sort(m_EntityRenderCommands.begin(), m_EntityRenderCommands.end());
    std::sort(m_EntityRenderCommands.begin(), m_EntityRenderCommands.end());
}

std::vector<RenderCommand> &MasterRenderer::GetCommandBufferByLayer(RenderLayer layer) {
    switch (layer) {
        case RenderLayer::Ground:
            return m_GroundRenderCommands;

        case RenderLayer::Entities:
            return m_EntityRenderCommands;
    }

    return m_EntityRenderCommands;
}
