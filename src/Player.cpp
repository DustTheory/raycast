#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Camera.hpp"

Player :: Player(sf::Vector2f _pos = {0, 0}) : GameObject(_pos, true, PLAYER), camera(new Camera(_pos)){}

Player :: Player(Camera* _camera, sf::Vector2f _pos = {0, 0}) : GameObject(_pos, true, PLAYER), camera(_camera){};

void Player :: handle_keyboard_input(){
	static const float movement_speed = 1e-3;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		pos.y += movement_speed;
	}	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		pos.x -= movement_speed;
	}	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		pos.y -= movement_speed;
	}	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		pos.x += movement_speed;
	}	
}
