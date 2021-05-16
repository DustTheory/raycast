#include <string>
#include <vector>

#ifndef MAP_H
#define MAP_H

enum MapCell {
    EmptyCell = 0,
    RedBrick,
    Wood,
    Eagle,
    Mossy,
    GreyStone,
    PurpleStone
};

class Map {
    int mapHeight;
    int mapWidth;
    std::vector<std::vector<MapCell>> map;
    public:
    Map();
    Map(std::vector<std::vector<int>> mapData);
    const std::vector<std::vector<MapCell>>& getMap() const;
    bool isOutOfBounds(int i, int j) const;
    MapCell atCoords(int i, int j) const;
    std::string toString() const;
    int getMapHeight() const;
    int getMapWidth() const;
};
#endif
