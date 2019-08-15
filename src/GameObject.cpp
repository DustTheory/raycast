#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

GameObject :: GameObject(sf::Vector2f _pos = {0, 0},
						 bool _visible_on_minimap = true,
						 GameObjectType _type = ITEM){
	pos = _pos;
	visible_on_minimap = _visible_on_minimap;
	type = _type;
}

