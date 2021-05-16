/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#ifndef LIB_ENTITY_H_
#define LIB_ENTITY_H_

#include<SFML/Graphics.hpp>

class Entity {
 protected:
    sf::Vector2f position;
    float rotation;
 public:
    virtual sf::Vector2f getPosition();
    virtual void setPosition(sf::Vector2f position);
    virtual void setRotation(float rotation);
};

#endif  // LIB_ENTITY_H_
