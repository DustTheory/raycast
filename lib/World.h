#include "Map.h"
#include "Entity.h"
#include <string>
#include <vector>


#ifndef WORLD_H
#define WORLD_H

class World {
    std::vector<Entity*> entities;
    public:
    Map map;
    World(Map map);
    World(std::string filename);
    void saveToFile(const std::string filename);
    int selectMapDataCallback(void *NotUsed, int argc, char **argv, char **szColName);
    void addEntity(Entity* entity);
    const std::vector<Entity*>& getEntities() const;
};

#endif