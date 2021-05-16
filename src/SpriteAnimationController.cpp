/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#include "SpriteAnimationController.h"
#include "AssetManager.h"

SpriteAnimation::SpriteAnimation() {}

SpriteAnimation::SpriteAnimation(const std::vector<nlohmann::basic_json<>> &frameList, int fps): fps(fps) {
    for (auto &frameRect : frameList)
        this->frameList.push_back(sf::IntRect(frameRect["x"],
                                                frameRect["y"],
                                                frameRect["w"],
                                                frameRect["h"]));
    duration = static_cast<float>(fps)/this->frameList.size();
}

SpriteAnimationController::SpriteAnimationController(sf::Sprite &sprite, std::string textureImgPath, std::string textureJsonPath): sprite(sprite) {
    texture = AssetManager::instance().getTexture(textureImgPath);
    json textureJson = AssetManager::instance().getTextureJson(textureJsonPath);
    for (auto it : textureJson.items())
        animations[it.key()] =
            SpriteAnimation(it.value()["frameList"], static_cast<int>(it.value()["fps"]));

    if (animations.size() == 0)
        throw std::runtime_error("SpriteAnimationController: No animations found in json.");

    sprite.setTexture(texture);
    setPlayingAnimation(animations.begin()->first);
}

void SpriteAnimationController::setPlayingAnimation(const std::string &animationName) {
    clock.restart();
    playingAnimation = animations.find(animationName);
    if (playingAnimation == animations.end())
        throw std::out_of_range("Invalid animation name requested from SpriteAnimationController");
}

void SpriteAnimationController::playAnimationOnce(const std::string &animationName, const std::string &fallback) {
    setPlayingAnimation(animationName);
    playingOnce = true;
    this->fallback = fallback;
}

void SpriteAnimationController::updateAnimationframe() {
    float t = clock.getElapsedTime().asSeconds();
    int framesElapsed = static_cast<int>(t*playingAnimation->second.fps);
    int frame = framesElapsed % playingAnimation->second.frameList.size();
    if (framesElapsed != 0 && frame == 0 && playingOnce) {
        playingOnce = false;
        setPlayingAnimation(fallback);
        updateAnimationframe();
        return;
    }

    sprite.setTextureRect(playingAnimation->second.frameList[frame]);
}
