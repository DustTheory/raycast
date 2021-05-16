/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#ifndef LIB_PLAYER_H_
#define LIB_PLAYER_H_

#include <SFML/Graphics.hpp>
#include "World.h"
#include "Camera.h"
#include "HUD.h"
#include "Entity.h"
#include "View.h"

class PlayerView : public View {
 public:
    Camera playerCamera;
    CameraView cameraView;
    HUD hud;

    bool showHUD;

    PlayerView(World* world, float width, float height);
    sf::Sprite getFrame();
};

class Player: Entity {
 public:
    sf::Window* window;
    PlayerView playerView;

    Player(sf::Window* window, World* world, sf::Vector2f position, float rotation);
    void setPosition(sf::Vector2f position);
    void setRotation(float rotation);
    void rotateBy(float delta);
    void moveForward(float moveSpeed);
    void fire();
    void reload();
    void handleEvent(const sf::Event &event);
};

#endif  // LIB_PLAYER_H_
