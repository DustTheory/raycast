#include "World.h"
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

World::World(Map map): map(map){}

// Loads World from world file
World::World(std::string filename){
    json wolrdJson;
    std::ifstream ifs(filename);
   
    if (!ifs.is_open()) 
        throw "Failed reading world file";

    ifs >> wolrdJson;
    map = Map(wolrdJson["map"]);

    ifs.close();    
}

void World::saveToFile(const std::string filename){
    json worldJson;
    worldJson["map"] = std::vector<std::vector<MapCell>>(map.getMap());
    std::ofstream ofs(filename);
    if (!ofs.is_open()) 
        throw "Failed opening world file";
    ofs << worldJson;
    ofs.close();        
}

void World::addEntity(Entity* entity){
    entities.push_back(entity);
}

const std::vector<Entity*>& World::getEntities() const{
    return entities;
}