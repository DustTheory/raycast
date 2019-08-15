#include <SFML/Graphics.hpp>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

enum GameObjectType{
	PLAYER = 0,
	ENEMY,
	ITEM,
	OTHER
};

class GameObject{
	private:

	public:
	sf::Vector2f pos;
	GameObjectType type;
	bool visible_on_minimap;
	GameObject();
	GameObject(sf::Vector2f _pos, bool _visible_on_minimap, GameObjectType _type);
};

#endif
