#include "memory/RscManager.hpp"

#include "globals/Constants.hpp"

Texture2D *RscManager::GetTexture(const TextureType type, const std::string &name) {
    if (m_TextureCache.find({(u8) type, name}) != m_TextureCache.end()) {
        return m_TextureCache[{(u8) type, name}];
    }

    std::string path = GetTexturePath(type, name);
    Texture2D *texture = new Texture2D();
    *texture = LoadTexture(path.c_str());

    m_TextureCache.insert({{(u8) type, name}, texture});

    spdlog::info("Texture loaded: {}", path);

    return texture;
}

SpriteSheet *RscManager::LoadSpriteSheet(const TextureType type, const std::string &name) {
    if (m_SpriteSheetCache.find({(u8) type, name}) != m_SpriteSheetCache.end()) {
        return m_SpriteSheetCache[{(u8) type, name}];
    }

    // For now just use 16x16 Frame Size for all Spritesheets
    // TODO Store such data in JSON File and load Data from there instead of Hard Coding
    SpriteSheet *ssheet = new SpriteSheet(m_SpriteSheetCount,
        GetTexture(type, name), TILE_SIZE, TILE_SIZE);

    m_SpriteSheetCache.insert({{(u8) type, name}, ssheet});
    m_SpriteSheetCacheIdLUT.insert({m_SpriteSheetCount, {(u8) type, name}});

    ++m_SpriteSheetCount;

    return ssheet;
}

SpriteSheet *RscManager::GetSpriteSheetById(const TextureType type, u32 id) {
    return m_SpriteSheetCache[m_SpriteSheetCacheIdLUT[id]];
}

std::string RscManager::GetTexturePath(const TextureType type, const std::string &name) {
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
