#include <SFML/Graphics.hpp>
#include <json.hpp>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

using json = nlohmann::json;

struct SpriteAnimation {
    std::vector<sf::IntRect> frameList;
    int fps;
    float duration;
    SpriteAnimation();
    SpriteAnimation(const std::vector<nlohmann::basic_json<>> &frameList, int fps);
};

class SpriteAnimationController {
    sf::Sprite& sprite;
    sf::Texture texture;
    std::map<std::string, SpriteAnimation> animations;
    std::map<std::string, SpriteAnimation>::iterator playingAnimation;
    json loadTextureFromFile(const std::string &textureImgPath, const std::string &textureJsonPath);
    sf::Clock clock;
    
    bool playingOnce=false;
    std::string fallback;

    public:
    SpriteAnimationController();
    SpriteAnimationController(sf::Sprite &sprite, std::string textureImgPath, std::string textureJsonPath);
    void setPlayingAnimation(const std::string &name);
    void playAnimationOnce(const std::string &name, const std::string &fallback);
    void updateAnimationframe();    
};

#endif