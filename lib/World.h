#include "Map.h"
#include <string>


#ifndef WORLD_H
#define WORLD_H

class World {
    public:
    Map map;
    World(Map map);
    World(std::string filename);
    void saveToFile(const std::string filename);
    int selectMapDataCallback(void *NotUsed, int argc, char **argv, char **szColName);
};

#endif