#include "memory/RscManager.hpp"

#include "globals/Constants.hpp"

#include <fstream>


void RscManager::LoadAssets()
{
    // -- Load File
    std::ifstream file(ASSETS_MANIFEST_PATH);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open Asset Manifest!");
        return;
    }

    json j;
    file >> j;

    std::unordered_map<std::string, Texture2D*> m_TextureCache;

    // -- Iterate Json File
    for (const auto& tex : j["textures"])
    {
        std::string _id = GetValue<std::string>(tex, "id");
        std::string _path = GetValue<std::string>(tex, "path");

        u32 _internalId = LoadTex(_id, _path);
        m_TexStrToId.insert({_id, _internalId});

        spdlog::info("Loaded Texture: {} : {}", _id, _path);
    }

    for (const auto& ssheet : j["sprite_sheets"])
    {
        std::string _id = GetValue<std::string>(ssheet, "id");
        u32 _textureId = m_TexStrToId[GetValue<std::string>(ssheet, "texture")];
        u32 _fWidth = GetValue<u32>(ssheet, "frame_width");
        u32 _fHeight = GetValue<u32>(ssheet, "frame_height");

        u32 _internalId = LoadSpriteSheet(_id, _textureId, _fWidth, _fHeight);
        m_SpriteSheetStrToId.insert({_id, _internalId});
    }

    // -- Populate Constant Asset IDs
    PopulateAssetBindings(RscType::Texture);
    PopulateAssetBindings(RscType::SpriteSheet);
}

Texture2D* RscManager::GetTexture(u32 id)
{
    if (id > m_TextureCache.size() - 1)
        return nullptr;

    return m_TextureCache[id];
}

SpriteSheet* RscManager::GetSpriteSheetById(u32 id)
{
    if (id > m_SpriteSheetCache.size() - 1)
        return nullptr;

    return m_SpriteSheetCache[id];
}

u32 RscManager::LoadTex(const std::string& id, const std::string& path)
{
    // Load Texture
    Texture2D* texture = new Texture2D();
    *texture = LoadTexture(path.c_str());

    m_TextureCache.push_back(texture);

    return m_TextureCache.size() - 1;
}

u32 RscManager::LoadSpriteSheet(const std::string& id, u32 textureId, u32 fWidth, u32 fHeight)
{
    u32 _id = m_SpriteSheetCache.size();

    SpriteSheet* spriteSheet = new SpriteSheet(_id, textureId, fWidth, fHeight);;
    m_SpriteSheetCache.push_back(spriteSheet);

    return _id;
}

void RscManager::PopulateAssetBindings(RscType type)
{
    switch (type)
    {
    case RscType::Texture:
        for (auto& b : textureBinding)
        {
            auto it = m_TexStrToId.find(b.m_Name);
            if (it == m_TexStrToId.end())
                throw std::runtime_error(std::string("Missing Texture: : ") + b.m_Name);

            *b.m_Target = it->second;
        }
        break;

    case RscType::SpriteSheet:
        for (auto& b : spriteSheetBinding)
        {
            auto it = m_SpriteSheetStrToId.find(b.m_Name);
            if (it == m_SpriteSheetStrToId.end())
                throw std::runtime_error(std::string("Missing Sprite Sheet: ") + b.m_Name);

            *b.m_Target = it->second;
        }
        break;

    default:
        spdlog::info("Populate Asset Binding Type {} not Implemented", (u32)type);
        break;
    }
}
