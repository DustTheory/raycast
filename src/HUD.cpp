#include <SFML/Graphics.hpp>
#include <fstream>
#include "HUD.h"
#include "SpriteAnimationController.h"


HUD::HUD(const World* world, float width, float height): View(width, height), world(world), minimap(world, height/5, height/5),  gunAnimationController(gunSprite, "assets/PistolTexture.png", "assets/PistolTexture.json"){
    gunAnimationController.setPlayingAnimation("still");
}

sf::Sprite HUD::getFrame(){
    gunAnimationController.updateAnimationframe();
    sf::IntRect tmp = gunSprite.getTextureRect();
    gunSprite.setScale(width/tmp.width, height/tmp.height);

    viewTexture.clear(sf::Color::Transparent);
    viewTexture.draw(minimap.getFrame());
    viewTexture.draw(gunSprite);
    viewTexture.display();
    return sf::Sprite(viewTexture.getTexture());
}

void HUD::startAnimation(const std::string &animationName){
    gunAnimationController.playAnimationOnce(animationName, "still");
}