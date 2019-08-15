#include <SFML/Graphics.hpp>
#include <vector>

#include "GameObject.hpp"

#ifndef WORLD_H
#define WORLD_H
class World{
	private:

	public:
	std::vector<GameObject*> game_objects;
	World();
	void add_object(GameObject* object);
};

#endif
