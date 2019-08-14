#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "Minimap.hpp"

int main(){
	Map map("./maps/json/emptyroom.json");
	Minimap minimap(&map);

	while(minimap.window->isOpen()){
		sf::Event event;
		while(minimap.window->pollEvent(event)){
			if(event.type == sf::Event::Closed)
				minimap.window->close();
		}
		
		minimap.window->clear();
		minimap.update_minimap();
		minimap.window->display();
	}
	return 0;
}
