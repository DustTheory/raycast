#include<SFML/Graphics.hpp>

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
    protected:
    sf::Vector2f position;
    float rotation;
    public:
    virtual sf::Vector2f getPosition();
    virtual void setPosition(sf::Vector2f position);
    virtual void setRotation(float rotation);
};

#endif