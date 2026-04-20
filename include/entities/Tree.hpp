#pragma once

#include "entities/Entity.hpp"
#include "graphics/SpriteSheet.hpp"

enum class TreeType
{
    Plain, // Holds no Fruits but gives more Wood
    Apple,
    Peach,
    Pear,
    Orange
};

class Tree : public virtual Entity
{
public:
    Tree(u32 id, const std::string& name = "",
         TreeType type = TreeType::Plain);
    ~Tree();

    virtual void Update() override;

    virtual RenderCommand CreateRenderCommand() override;

    virtual void Render() override;

    TreeType GetType() const { return m_TreeType; }

private:
    TreeType m_TreeType;

    static SpriteSheet* m_TreeSpriteSheet;
    SpriteSheet* m_FruitSpriteSheet;
};
