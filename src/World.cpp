/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#include "World.h"
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

World::World(Map map): map(map) {}

// Loads World from world file
World::World(std::string filename) {
    json wolrdJson;
    std::ifstream ifs(filename);

    if (!ifs.is_open())
        throw "Failed reading world file";

    ifs >> wolrdJson;
    map = Map(wolrdJson["map"]);

    ifs.close();
}

void World::saveToFile(const std::string filename) {
    json worldJson;
    const std::vector<std::vector<MapCell>> &mapData = map.getMap();
    std::vector<std::vector<int>> mapDataInt(
                                    map.getMapHeight(),
                                    std::vector<int>(map.getMapWidth()));

    for (int i = 0; i < static_cast<int>(map.getMapHeight()); i++)
        for (int j = 0; j < static_cast<int>(map.getMapWidth()); j++)
            mapDataInt.at(i).at(j) = static_cast<int>(mapData.at(i).at(j));
    worldJson["map"] = mapDataInt;

    std::ofstream ofs(filename);
    if (!ofs.is_open())
        throw "Failed opening world file";
    ofs << worldJson;
    ofs.close();
}

void World::addEntity(Entity* entity) {
    entities.push_back(entity);
}

const std::vector<Entity*>& World::getEntities() const {
    return entities;
}
