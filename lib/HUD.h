#include<SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Minimap.h"
#include "json.hpp"
#include "SpriteAnimationController.h"

using json = nlohmann::json;

#ifndef HUD_H
#define HUD_H

class HUD : public View{
    const World* world;
    sf::Sprite gunSprite;
    Minimap minimap;
    SpriteAnimationController gunAnimationController;

    public:
    HUD(const World* world, float width, float height);
    sf::Sprite getFrame();
    void startAnimation(const std::string &animationName);
};

#endif