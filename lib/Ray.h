/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */

#ifndef LIB_RAY_H_
#define LIB_RAY_H_

#include <Entity.h>
#include <SFML/Graphics.hpp>

struct RayMapHit {
    sf::Vector2f pos;
    sf::Vector2i mapPos;
    bool side;
};

struct RayEntityHit {
    sf::Vector2f pos;
    Entity* entityHit;
};

class Ray {
 public:
    sf::Vector2f origin;
    sf::Vector2f direction;
    Ray();
    Ray(sf::Vector2f origin, sf::Vector2f direction);
    bool mapStep(sf::Vector2f &position);
    float yOnRay(float x);
    float xOnRay(float y);
};

#endif  // LIB_RAY_H_
