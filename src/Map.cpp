#include <stdexcept>
#include "Map.h"

Map::Map(): mapHeight(0), mapWidth(0){};

Map::Map(std::vector<std::vector<int>> mapData){
	mapHeight = mapData.size();
	mapWidth = mapHeight > 0 ? mapData[0].size() : 0;
	map.clear();
	for(int i = 0; i < mapHeight; i++){
		map.push_back({});
		for(int j = 0; j < mapWidth; j++)
			map[i].push_back((MapCell)mapData.at(i).at(j));
	}
}



bool Map::isOutOfBounds(int i, int j) const{
     return i < 0 || j < 0 || i >= mapHeight || j >= mapWidth;
}

MapCell Map::atCoords(int i, int j) const{
	return map.at(i).at(j);
}

 const std::vector<std::vector<MapCell>>& Map::getMap() const{
	return map;
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