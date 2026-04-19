#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <raylib.h>
#include <spdlog/spdlog.h>

#include "tenshiUtil/Types.h"
#include "graphics/SpriteSheet.hpp"
#include "globals/Constants.hpp"
#include "tenshiUtil/io/json.hpp"

using json = nlohmann::json;

enum class RscType : u8
{
    Texture,
    SpriteSheet,
    Sprite,     // A Frame in a Sprite Sheet
    Sound,
    Music,
    Font
};

#pragma region Assets
struct AssetBinding
{
    AssetBinding() {}
    AssetBinding(const char* name, u32* target)
        : m_Name(name), m_Target(target) {}

    const char *m_Name = "";
    u32* m_Target = nullptr;
};

// We Populate the Asset IDs during Loading
namespace Textures
{
    inline u32 Player;
    inline u32 GrassTiles;
}

inline AssetBinding textureBinding[] = {
    {"Player", &Textures::Player},
    {"Grass_Tiles", &Textures::GrassTiles}
};

namespace SpriteSheets
{
    inline u32 Player;
    inline u32 GrassTiles;
}

inline AssetBinding spriteSheetBinding[] = {
    {"Player", &SpriteSheets::Player},
    {"Grass_Tiles", &SpriteSheets::GrassTiles}
};

#pragma endregion

// Used for Rsc Key Lookup
// Manifest ID Strings get hashed to a u32 for better Look up
// We store a LUT to map the Names to the IDs
struct RscKey {
    RscKey() {}

    RscKey(RscType type, u32 id)
        : m_Type(type), m_Id(id) {
    }

    RscType m_Type = RscType::Texture;
    u32 m_Id = 1337;

    bool operator==(const RscKey &rhs) const {
        return (m_Type == rhs.m_Type) && (m_Id == rhs.m_Id);
    }
};

template<>
struct std::hash<RscKey> {
    std::size_t operator()(const RscKey &key) const noexcept {
        return std::hash<u8>()((u8)key.m_Type) ^ (std::hash<u32>()(key.m_Id) << 1);
    }
};

class RscManager {
public:
    // Load Assets from AssetsManifest.json File
    void LoadAssets();

    Texture2D *GetTexture(u32 id);

    // Only returns a valid Pointer if LoadSpriteSheet was called before
    SpriteSheet *GetSpriteSheetById(u32 id);

private:
    // Returns the ID of the Texture
    u32 LoadTex(const std::string& id, const std::string& path);
    u32 LoadSpriteSheet(const std::string& id, u32 textureId,
        u32 fWidth, u32 fHeight);

    void PopulateAssetBindings(RscType type);

    template <typename T>
    static T GetValue(const json& j, const char* key)
    {
        T _value;

        if (!j.contains(key))
            throw std::runtime_error(std::string("Missing Key in Manifest: ") + key);

        return j[key].get<T>();
    }

private:
    const std::string ASSETS_MANIFEST_PATH = "assets/AssetsManifest.json";

    std::vector<Texture2D*> m_TextureCache;
    std::vector<SpriteSheet*> m_SpriteSheetCache;

    // Only use this for Initial Asset Loading + Debug
    std::unordered_map<std::string, u32> m_TexStrToId;
    std::unordered_map<std::string, u32> m_SpriteSheetStrToId;
};
