/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#include "Map.h"
#include "Entity.h"
#include "Player.h"

#ifndef LIB_WORLD_H_
#define LIB_WORLD_H_

#include <string>
#include <vector>

class World {
    std::vector<Entity*> entities;
 public:
    Map map;
    explicit World(Map map);
    explicit World(std::string filename);
    void saveToFile(const std::string filename);
    void addEntity(Entity* entity);
    const std::vector<Entity*>& getEntities() const;
};

#endif  // LIB_WORLD_H_
