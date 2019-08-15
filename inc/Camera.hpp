#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

#ifndef CAMERA_H
#define CAMERA_H

class Camera: public GameObject{
	public:
	Camera(sf::Vector2f _pos);
};

#endif
