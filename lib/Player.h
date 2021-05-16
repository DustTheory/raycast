

#ifndef PLAYERCONTROLER_H
#define PLAYERCONTROLER_H

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

class Player: Entity{   
    public:
    PlayerView playerView;

    Player(World* world, sf::Vector2f position, float rotation);
    void setPosition(sf::Vector2f position);
    void setRotation(float rotation);
    void rotateBy(float delta);
    void moveForward(float moveSpeed);
    void fire();
    void reload();
    void handleEvent(sf::Event &event);
};

#endif