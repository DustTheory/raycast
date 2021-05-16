/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#include <SFML/Graphics.hpp>
#include "Player.h"

float moveSpeed = 0.3;
float rotateSpeed = degToRad(3.5);

PlayerView::PlayerView(World* world, float width, float height): View(width, height), playerCamera(world, width), cameraView(&playerCamera, width, height), hud(world, width, height) {
    world->addEntity(&playerCamera);
}

sf::Sprite PlayerView::getFrame() {
    viewTexture.clear(sf::Color::Black);

    playerCamera.captureFrame();
    viewTexture.draw(cameraView.getFrame());
    viewTexture.draw(hud.getFrame());

    viewTexture.display();
    return sf::Sprite(viewTexture.getTexture());
}

Player::Player(sf::Window* window, World* world, sf::Vector2f position, float rotation):
    window(window),
    playerView(world, window->getSize().x, window->getSize().y)
{
    setPosition(position);
    setRotation(rotation);
}

void Player::setPosition(sf::Vector2f position) {
    auto cellAtNextPos = playerView.playerCamera.getWorld()->map.atCoords(
        static_cast<int>(position.x),
        static_cast<int>(position.y));
    if (cellAtNextPos == MapCell::EmptyCell)
        playerView.playerCamera.setPosition(this->position = position);
}

void Player::setRotation(float rotation) {
    playerView.playerCamera.setRotation(this->rotation = rotation);
}

void Player::rotateBy(float delta) {
    setRotation(rotation+delta);
}

float distNoRoot(sf::Vector2f v1, sf::Vector2f v2) {
    return (v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y);
}

void Player::moveForward(float moveSpeed) {
    setPosition(getPosition() +
                playerView.playerCamera.getLookDirection() * moveSpeed);
}

void Player::fire() {
    playerView.hud.startAnimation("shoot");
}

void Player::reload() {
    playerView.hud.startAnimation("reload");
}

void Player::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        char key = event.key.code + 'a';
        if (key == 'w' || key == 'W')
            moveForward(moveSpeed);

        if (key == 'a' || key == 'A')
            rotateBy(-rotateSpeed);

        if (key == 's' || key == 'S')
            moveForward(-moveSpeed);

        if (key == 'd' || key == 'D')
            rotateBy(rotateSpeed);

        if (key == 'r' || key == 'R')
            reload();

        if (event.key.code == sf::Keyboard::Space)
            fire();
    }
}

