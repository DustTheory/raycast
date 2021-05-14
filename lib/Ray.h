#include <SFML/Graphics.hpp>

#ifndef RAY_H
#define RAY_H

struct RayHit {
    sf::Vector2f pos;
    sf::Vector2i mapPos;
    bool side;
};

class Ray {
    public:
    sf::Vector2f origin;
    sf::Vector2f direction;
    Ray(sf::Vector2f origin, sf::Vector2f direction);
    bool mapStep(sf::Vector2f &position);
    float yOnRay(float x);
    float xOnRay(float y);
};

#endif