/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#include "Entity.h"

sf::Vector2f Entity::getPosition() {
    return position;
}

void Entity::setPosition(sf::Vector2f position) {
    this->position = position;
}
void Entity::setRotation(float rotation) {
    this->rotation = rotation;
}
