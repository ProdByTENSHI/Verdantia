#include "render/MasterRenderer.hpp"
#include "globals/Globals.hpp"
#include "globals/Events.hpp"

MasterRenderer::MasterRenderer()
{
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::Render()
{
    BeginDrawing();
    BeginMode2D(g_Camera->GetCamera());
    OnRender.Dispatch();

    StageRenderCmdBuffers();

    RenderDrawCommandBuffer(m_GroundRenderCommands);
    RenderDrawCommandBuffer(m_EntityRenderCommands);

    ClearBackground(RAYWHITE);

    EndMode2D();

    // -- RENDER UI HERE LATER

    EndDrawing();

    m_GroundRenderCommands.clear();
    m_EntityRenderCommands.clear();
}

void MasterRenderer::PushRenderCommand(RenderLayer layer, RenderCommand cmd)
{
    GetCommandBufferByLayer(layer).push_back(cmd);
}

void MasterRenderer::StageRenderCmdBuffers()
{
    // -- Sort Render Command Buffers
    std::sort(m_EntityRenderCommands.begin(), m_EntityRenderCommands.end());
    std::sort(m_EntityRenderCommands.begin(), m_EntityRenderCommands.end());
}

std::vector<RenderCommand>& MasterRenderer::GetCommandBufferByLayer(RenderLayer layer)
{
    switch (layer)
    {
    case RenderLayer::Ground:
        return m_GroundRenderCommands;

    case RenderLayer::Entities:
        return m_EntityRenderCommands;
    }

    return m_EntityRenderCommands;
}

void MasterRenderer::RenderDrawCommandBuffer(const std::vector<RenderCommand>& buffer) const
{
    u32 _lastTextureId = 0;
    SpriteSheet* _spriteSheet = nullptr;
    Texture2D _texture;

    for (i32 i = 0; i < buffer.size(); i++)
    {
        RenderCommand _cmd = buffer[i];
        if (_lastTextureId != _cmd.m_TextureId)
        {
            _lastTextureId = m_GroundRenderCommands[i].m_TextureId;
            _spriteSheet = g_RscManager->GetSpritesheet(_lastTextureId);
            _texture = *g_RscManager->GetTexture(_spriteSheet->GetTexture());
        }

        DrawTextureRec(_texture, _cmd.m_SrcRect, _cmd.m_Position, WHITE);
    }
}
