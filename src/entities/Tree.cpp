#include "entities/Tree.hpp"

#include "globals/Globals.hpp"

Tree::Tree(u32 id, const std::string& name, TreeType type)
    : Entity(id, name)
{
}

Tree::~Tree()
{
}

void Tree::Update()
{
}

RenderCommand Tree::CreateRenderCommand()
{
    RenderCommand _cmd;

    _cmd.m_Position = m_Position;
    _cmd.m_TextureId = Textures::TreeBase;
    _cmd.m_SrcRect = {0, 0, 48, 48};

    return _cmd;
}

void Tree::Render()
{
}
