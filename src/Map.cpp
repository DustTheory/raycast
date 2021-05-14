#include <stdexcept>
#include "Map.h"

Map::Map(): mapHeight(0), mapWidth(0){};

Map::Map(std::string mapdata, int mapHeight, int mapWidth): mapHeight(mapHeight), mapWidth(mapWidth) {
	if((int)mapdata.length() != mapHeight*mapWidth)
		throw std::out_of_range("Map dimensions incompatible with map data");
	this->map = std::vector<std::vector<MapCell>>(mapHeight, std::vector<MapCell>(mapWidth, MapCell::EmptyCell));
	for(int i = 0; i < mapHeight; i++)
		for(int j = 0; j < mapWidth; j++)
			this->map.at(i).at(j) = (MapCell)(mapdata[i*mapWidth+j]-'0');
}


bool Map::isOutOfBounds(int i, int j) const{
     return i < 0 || j < 0 || i >= mapHeight || j >= mapWidth;
}

MapCell Map::atCoords(int i, int j) const{
	return map.at(i).at(j);
}

std::string Map::toString() const{
	std::string res;
	res.reserve(mapWidth*mapHeight+10);
	for(int i = 0; i < mapHeight; i++)
		for(int j = 0; j < mapWidth; j++)
			res+= '0' + map[i][j];
	return res;
}

int Map::getMapWidth() const{
	return mapWidth;
}

int Map::getMapHeight() const{
	return mapHeight;
}