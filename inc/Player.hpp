#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"

#ifndef PLAYER_H
#define PLAYER_H

class Player: public GameObject{
	public:
	Camera* camera;	
	Player(sf::Vector2f _pos);
	Player(Camera* _camera, sf::Vector2f _pos);
	void handle_keyboard_input();
};

#endif
