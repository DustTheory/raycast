#include <SFML/Graphics.hpp>
#include <vector>

#include "View.h"
#include "World.h"
#include "Camera.h"

#ifndef MINIMAP_H
#define MINIMAP_H


class Minimap : public View {
    const World* world;
    float cellSide;  
    sf::Color mapColor(MapCell cell);
    void drawCamera(Camera* camera);
    public:
    Minimap(const World* world, float width, float height);
    sf::Sprite getFrame();
};

#endif