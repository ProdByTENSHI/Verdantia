#pragma once

#include "entities/Entity.hpp"

class Player : virtual public Entity {
public:
    Player(u32 id);
    ~Player();

    void Update() override;
    void Render() override;

private:
};