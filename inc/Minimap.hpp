#include <SFML/Graphics.hpp>
#include "Map.hpp"

#ifndef MINIMAP_H
#define MINIMAP_H

// Height and width of the minimap window
#define MINIMAP_W_HEIGHT 200
#define MINIMAP_W_WIDTH 200

class Minimap{
	private:
		Map* map;
		sf::Uint8* map_pixels;
		sf::Texture map_texture;
		sf::Sprite map_sprite;
		int m_w, m_h; // Dimensions of minimap texture, equal to map dimensions	

	public:
	sf::RenderWindow* window;

	void setup_window();
	Minimap(Map* _map);
	void update_minimap();
	void update_map_overlay();
	void update_map();
};

#endif
