/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#ifndef LIB_ASSETMANAGER_H_
#define LIB_ASSETMANAGER_H_

#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include "json.hpp"

using json = nlohmann::json;

class AssetManager {
 private:
    std::map<std::string, sf::Texture> texturesMap;
    std::map<std::string, json> textureJsonMap;
 public:
    AssetManager();
    static AssetManager& instance();
    static const sf::Texture& getTexture(const std::string &filename, bool makeRepeated = false);
    static const json& getTextureJson(const std::string &filename);
};

#endif  // LIB_ASSETMANAGER_H_
