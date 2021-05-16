/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */

#include <assert.h>
#include <fstream>
#include <iostream>

#include "AssetManager.h"


AssetManager::AssetManager() {}

AssetManager& AssetManager::instance() {
    static AssetManager INSTANCE;
    return INSTANCE;
}

const sf::Texture& AssetManager::getTexture(const std::string &filename, bool makeRepeated) {
    auto& textureMap = instance().texturesMap;
    auto textureIt = textureMap.find(filename);
    if (textureIt != textureMap.end())
        return textureIt->second;
    auto& texture = textureMap[filename];
    if (!texture.loadFromFile(filename))
        std::cerr << "Texture file not found at: " << filename << std::endl;
    texture.setRepeated(true);
    return texture;
}

const json& AssetManager::getTextureJson(const std::string &filename) {
    auto& textureJsonMap = instance().textureJsonMap;
    auto textureJsonIt = textureJsonMap.find(filename);
    if (textureJsonIt != textureJsonMap.end())
        return textureJsonIt->second;

    std::ifstream ifs(filename);
    json &textureJson = textureJsonMap[filename];
    if (!ifs.is_open())
        std::cerr << "Texture json file not found at:" << filename << std::endl;
    ifs >> textureJson;
    ifs.close();
    return textureJson;
}
