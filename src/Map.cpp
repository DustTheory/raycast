/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#include <iostream>

#include <stdexcept>
#include "Map.h"
#include "AssetManager.h"

Map::Map() {}

Map::Map(std::vector<std::vector<int>> mapData) {
    map.clear();
    for (int i = 0; i < static_cast<int>(mapData.size()); i++) {
        map.push_back({});
        for (int j = 0; j < static_cast<int>(mapData[i].size()); j++)
            map[i].push_back(MapCell(mapData.at(i).at(j)));
    }
}

bool Map::isOutOfBounds(int i, int j) const {
    return i < 0 || j < 0 || i >= getMapHeight() || j >= getMapWidth();
}

MapCell Map::atCoords(int i, int j) const {
    if (isOutOfBounds(i, j))
        return MapCell::EmptyCell;
    return map.at(i).at(j);
}

const std::vector<std::vector<MapCell>>& Map::getMap() const {
    return map;
}

int Map::getMapWidth() const {
    return map.size();
}

int Map::getMapHeight() const {
    return map.size() > 0 ? map[0].size() : 0;
}

const sf::Texture MapCell::mapTexture =
    AssetManager::instance().getTexture("assets/maptexture.png", true);

const json MapCell::mapTextureJson =
    AssetManager::instance().getTextureJson("assets/maptexture.json");

const MapCell MapCell::EmptyCell = MapCell(0);

MapCell::MapCell(int mapCellId): mapCellId(mapCellId) {
    if (mapCellId == 0) {
        cellTxRect = {0, 0, 0, 0};
    } else if ( mapCellId-1 >= 0 &&
                mapCellId-1 < static_cast<int>(mapTextureJson["frames"].size())) {
        auto& tmp = mapTextureJson["frames"].at(mapCellId-1)["frame"];
        cellTxRect = sf::IntRect(tmp["x"], tmp["y"], tmp["w"], tmp["h"]);
    } else {
        throw std::runtime_error("Reference to non existent texture");
    }
}

const sf::IntRect& MapCell::getTxRect() {
    return cellTxRect;
}
