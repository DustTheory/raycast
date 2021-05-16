/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#include "World.h"
#include "Camera.h"
#include "View.h"

#ifndef LIB_MINIMAP_H_
#define LIB_MINIMAP_H_

#include <SFML/Graphics.hpp>

class Minimap : public View {
    const World* world;
    float cellSide;
    sf::Color mapColor(MapCell cell);
    void drawCamera(Camera* camera);
 public:
    Minimap(const World* world, float width, float height);
    sf::Sprite getFrame();
};

#endif  // LIB_MINIMAP_H_
