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
    float relativeAngle; // Only used in camera to store relative angle to look direction, useful for fisheye correction
    Ray();
    Ray(sf::Vector2f origin, sf::Vector2f direction, float relativeAngle=0);
    bool mapStep(sf::Vector2f &position);
    float yOnRay(float x);
    float xOnRay(float y);
};

#endif