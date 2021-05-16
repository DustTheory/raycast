#include "Player.h"

float moveSpeed = 0.3;
float rotateSpeed = degToRad(2);

PlayerView::PlayerView(World* world, float width, float height): View(width, height), playerCamera(world), cameraView(&playerCamera, width, height), hud(world, width, height){
    world->addEntity(&playerCamera);
}

sf::Sprite PlayerView::getFrame(){
    viewTexture.clear(sf::Color::Black);

    playerCamera.captureFrame();
    viewTexture.draw(cameraView.getFrame());
    viewTexture.draw(hud.getFrame());

    viewTexture.display();
    return sf::Sprite(viewTexture.getTexture());
}

Player::Player(World* world, sf::Vector2f position, float rotation): playerView(world, 800, 600){
    setPosition(position);
    setRotation(rotation);
}

void Player::setPosition(sf::Vector2f position){
    playerView.playerCamera.setPosition(this->position = position);
}

void Player::setRotation(float rotation){
    playerView.playerCamera.setRotation(this->rotation = rotation);
}

void Player::rotateBy(float delta){
    setRotation(rotation+delta);
}

void Player::moveForward(float moveSpeed){
    setPosition(getPosition()+playerView.playerCamera.getLookDirection()*moveSpeed);
}

void Player::fire(){
    playerView.hud.startAnimation("shoot");
}

void Player::reload(){
    playerView.hud.startAnimation("reload");
}

void Player::handleEvent(sf::Event &event){
    if (event.type == sf::Event::KeyPressed){
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
            
        if(event.key.code == sf::Keyboard::Space)
            fire();
    }
}

