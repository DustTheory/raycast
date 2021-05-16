/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#ifndef LIB_SPRITEANIMATIONCONTROLLER_H_
#define LIB_SPRITEANIMATIONCONTROLLER_H_

#include <vector>
#include <map>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <json.hpp>


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
    sf::Clock clock;

    bool playingOnce = false;
    std::string fallback;

 public:
    SpriteAnimationController();
    SpriteAnimationController(sf::Sprite &sprite, std::string textureImgPath, std::string textureJsonPath);
    void setPlayingAnimation(const std::string &name);
    void playAnimationOnce(const std::string &name, const std::string &fallback);
    void updateAnimationframe();
};

#endif  // LIB_SPRITEANIMATIONCONTROLLER_H_
