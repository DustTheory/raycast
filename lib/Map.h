#include <string>
#include <vector>

#ifndef MAP_H
#define MAP_H

enum MapCell {
    EmptyCell = 0,
    Wall1,
    Wall2,
    Wall3,
    Wall4,
    Wall5
};

class Map {
    int mapHeight;
    int mapWidth;
    std::vector<std::vector<MapCell>> map;
    public:
    Map();
    Map(std::string mapdata, int mapHeight, int mapWidth);
    bool isOutOfBounds(int i, int j) const;
    MapCell atCoords(int i, int j) const;
    std::string toString() const;
    int getMapHeight();
    int getMapWidth();
};
#endif
