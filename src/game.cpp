#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "Minimap.hpp"
#include "World.hpp"
#include "Player.hpp"

int main(){
	Map map("./maps/json/emptyroom.json");
	World gameWorld;
	Minimap minimap(&map, &gameWorld);
	Player* player = new Player(sf::Vector2f(map.get_spawnpoint()));
	
	gameWorld.add_object(player);

	while(minimap.window->isOpen()){
		sf::Event event;
		while(minimap.window->pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
					minimap.window->close();
					break;
				
				default:
					  break;
			}
		}
		
		player->handle_keyboard_input();		


		minimap.window->clear();
		minimap.update_minimap();
		minimap.window->display();
	}
	return 0;
}

