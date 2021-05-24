#include <resources.h>
#include <assets/cactusPreset.h>
#include <json.hpp>
#include <utils/jsonHelpers.h>
#include <jsonImporters.h>
#include <sstream>
#include <fstream>

template<>
static void wok::res::create(const std::string& name, CactusPreset& asset)
{
    auto data = loadJsonFile(name);

    asset.textureName = getAssetPath(name, data["texture_name"]);
    asset.textureRect = data.at("texture_rect").get<sf::IntRect>();

    asset.animationScale = data.at("animation_scale").get<float>();
    asset.startingHealth = data.at("starting_health").get<int>();

    asset.fractures.clear();
    for (auto& fracture : data.at("fractures"))
    {
        asset.fractures.push_back(fracture.get<sf::IntRect>());
    }
}