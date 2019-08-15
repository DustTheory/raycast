#include <SFML/Graphics.hpp>
#include <vector>
#include "World.hpp"
#include "GameObject.hpp"

World :: World(){}

void World :: add_object(GameObject* object){
	game_objects.push_back(object);	
}
