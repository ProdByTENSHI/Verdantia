#include "memory/RscManager.hpp"

Texture2D *RscManager::GetTexture(TextureType type, std::string name) {
    if (m_TextureCache.find({(u8)type, name}) != m_TextureCache.end()) {
        return m_TextureCache[{(u8)type, name}];
    }

    std::string path = GetTexturePath(type, name);
    Texture2D* texture = new Texture2D();
    *texture = LoadTexture(path.c_str());

    m_TextureCache.insert({{(u8)type, name}, texture});
    return texture;
}

std::string RscManager::GetTexturePath(TextureType type, std::string name) {
    std::string path = "assets/sprites/";

    switch (type) {
        case TextureType::GroundTile:
            path += "Tilesets/ground/";
            break;

        case TextureType::Building:
            path += "Tilesets/Buildings";
            break;

        case TextureType::AnimalBuilding:
            path += "Tilesets/Buildings/Animal";
            break;

        case TextureType::Object:
            path += "Objects/";
            break;

        case TextureType::Player:
            path += "Player/";
            break;

        case TextureType::Animal:
            path += "Animals/";
            break;

    }

    path += name;
    return path;
}
