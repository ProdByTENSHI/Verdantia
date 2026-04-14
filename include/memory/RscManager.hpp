#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <raylib.h>
#include <spdlog/spdlog.h>

#include "tenshiUtil/Types.h"
#include "graphics/SpriteSheet.hpp"

enum class TextureType : u8 {
    GroundTile,
    Building,
    AnimalBuilding,
    Object,
    Player,
    Animal
};

// Used for Rsc Key Lookup
struct RscKey {
    RscKey(u8 type, const std::string &name) : m_Type(type), m_Name(name) {
    }

    u8 m_Type = 0;
    std::string m_Name = "";

    bool operator==(const RscKey &rhs) const {
        return m_Type == rhs.m_Type && m_Name == rhs.m_Name;
    }
};

template<>
struct std::hash<RscKey> {
    std::size_t operator()(const RscKey &key) const noexcept {
        return std::hash<u8>()(key.m_Type) ^ (std::hash<string>()(key.m_Name) << 1);
    }
};

class RscManager {
public:
    Texture2D *GetTexture(const TextureType type, const std::string &name);

    SpriteSheet *GetSpriteSheet(const TextureType type, const std::string &name);

    static std::string GetTexturePath(const TextureType type, const std::string &name);

private:
    std::unordered_map<RscKey, Texture2D *> m_TextureCache;
    std::unordered_map<RscKey, SpriteSheet *> m_SpriteSheetCache;
};
