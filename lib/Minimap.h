#include <SFML/Graphics.hpp>
#include <vector>
#include "World.h"
#include "Camera.h"

#ifndef MINIMAP_H
#define MINIMAP_H


class Minimap {
    const World* world;
    sf::RenderTexture texture;
    int width, height;
    float cellSide;  
    sf::Color mapColor(MapCell cell);
    void drawCamera(Camera* camera);
    public:
    Minimap(const World* world, int width=500, int height=500);
    sf::Sprite getFrame();
};

#endif