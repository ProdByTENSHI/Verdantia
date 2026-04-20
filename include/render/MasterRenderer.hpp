#pragma once

#include "tenshiUtil/Types.h"
#include "globals/Constants.hpp"
#include "render/RenderCommand.hpp"

#include <raylib.h>
#include <vector>
#include <unordered_map>

class MasterRenderer
{
public:
    MasterRenderer();

    ~MasterRenderer();

    void PushRenderCommand(RenderLayer layer, RenderCommand cmd);

    void Render();

private:
    void StageRenderCmdBuffers();
    void RenderDrawCommandBuffer(const std::vector<RenderCommand>& buffer) const;
    void DrawWater();

    std::vector<RenderCommand>& GetCommandBufferByLayer(RenderLayer layer);

private:
    std::vector<RenderCommand> m_GroundRenderCommands;
    std::vector<RenderCommand> m_EntityRenderCommands;

    Texture2D m_WaterTexture;
};
