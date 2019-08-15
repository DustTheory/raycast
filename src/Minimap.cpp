#include "Minimap.hpp"
#include "World.hpp"

void Minimap :: setup_window(){
	window = new sf::RenderWindow(sf::VideoMode(MINIMAP_W_WIDTH, MINIMAP_W_HEIGHT), "Minimap");
	map_pixels = new sf::Uint8[m_w*m_h*4];
	map_texture.create(m_w, m_h);
	map_sprite = sf::Sprite(map_texture);
	sf::Vector2f target_size(window->getSize().x, window->getSize().y);
	map_sprite.setScale(
		target_size.x / map_sprite.getLocalBounds().width,
		target_size.y / map_sprite.getLocalBounds().height);
}

Minimap :: Minimap(Map* _map = new Map(), World* _game_world = new World()) : map(_map), game_world(_game_world){
	m_w = map->get_width();
	m_h = map->get_height();
	setup_window();
}

void Minimap :: update_minimap(){
	update_map();
	update_map_overlay();
}

void Minimap :: update_map_overlay(){
	for(GameObject* o : game_world->game_objects){
		if(!o->visible_on_minimap)
				continue;
		sf::CircleShape marker(10);	//size
		marker.setPosition(map_coords_to_minimap_window_coords(o->pos));
		marker.setFillColor(sf::Color::Red);
		window->draw(marker);
	}	
}

void Minimap :: update_map(){
	sf::Color* c;
	for(register int i = 0, j = 0; i < m_w*m_h*4; i+=4){
		c = &map->at_pos(j)->color;
		map_pixels[i] = c->r;
		map_pixels[i+1] = c->g;
		map_pixels[i+2] = c->b;
		map_pixels[i+3] = c->a;
		j++;
	}
	map_texture.update(map_pixels);
	
	window->draw(map_sprite);
}

sf::Vector2f Minimap :: map_coords_to_minimap_window_coords(sf::Vector2f map_coords){
	return {
		map_coords.x * window->getSize().x / m_w,
		map_coords.y * window->getSize().y / m_h
	};
}

