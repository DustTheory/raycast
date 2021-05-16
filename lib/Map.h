/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#ifndef LIB_MAP_H_
#define LIB_MAP_H_

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "json.hpp"

using json = nlohmann::json;

class MapCell {
    int mapCellId;
    sf::IntRect cellTxRect;
 public:
    static const sf::Texture mapTexture;
    static const json mapTextureJson;
    static const MapCell EmptyCell;

    explicit MapCell(int mapCellId);
    const sf::IntRect& getTxRect();

    operator int() const {
        return mapCellId;
    }

    bool operator==(const MapCell & other) {
        return mapCellId == static_cast<int>(other);
    }
};

class Map {
    std::vector<std::vector<MapCell>> map;
 public:
    Map();
    explicit Map(std::vector<std::vector<int>> mapData);
    const std::vector<std::vector<MapCell>>& getMap() const;
    bool isOutOfBounds(int i, int j) const;
    MapCell atCoords(int i, int j) const;
    std::string toString() const;
    int getMapHeight() const;
    int getMapWidth() const;
};
#endif  // LIB_MAP_H_
