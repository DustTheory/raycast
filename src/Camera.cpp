#include <SFML/Graphics.hpp>
#include "Camera.hpp"

Camera :: Camera(sf::Vector2f _pos = {0, 0}) : GameObject(_pos, false, OTHER){}

