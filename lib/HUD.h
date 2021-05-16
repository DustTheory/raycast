/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#include <map>
#include <string>

#include<SFML/Graphics.hpp>
#include "World.h"
#include "Minimap.h"
#include "json.hpp"
#include "SpriteAnimationController.h"

#ifndef LIB_HUD_H_
#define LIB_HUD_H_

using json = nlohmann::json;

class HUD : public View {
    const World* world;
    sf::Sprite gunSprite;
    Minimap minimap;
    SpriteAnimationController gunAnimationController;

 public:
    HUD(const World* world, float width, float height);
    sf::Sprite getFrame();
    void startAnimation(const std::string &animationName);
};

#endif  // LIB_HUD_H_
