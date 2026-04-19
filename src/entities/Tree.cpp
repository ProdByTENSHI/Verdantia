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
    return _cmd;
}

void Tree::Render()
{
}
