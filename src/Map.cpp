#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "json.hpp"

#include "Map.hpp"

using json = nlohmann::json;

Block :: Block(){
	color = sf::Color::Magenta;
	visible = colliding = true;
}

Block :: Block(sf::Color _color, bool _visible , bool _colliding ){
	color = _color;
	visible = _visible;
	colliding = _colliding;
}

// Define base blocks
Block ground = Block(sf::Color::Transparent, false, false);
Block wall_blue = Block(sf::Color::Blue);


std::vector<Block> block_types{
	ground,
	wall_blue
};

Map :: Map() : h(0), w(0), spawnpoint({0, 0}) {};

Map ::Map(std::string map_filepath){
	load_map_file(map_filepath);
}
	
void Map :: load_map_file(std::string map_filepath){
		std::ifstream input_stream(map_filepath);
		std::string tmp( (std::istreambuf_iterator<char>(input_stream) ),
						 (std::istreambuf_iterator<char>()             ) );	
		json map_json = json::parse(tmp);
		
//		h = map_json["height"];
//		w = map_json["weight"];

//		map = map_json["map"].get<std::vector<uint8_t>>();
	
	//	spawnpoint = {map_json["spawnpoint_x"], map_json["spawnpoint_y"]};

	}

int Map :: get_height(){
	return h;
}

int Map :: get_width(){
	return w;
}

sf::Vector2<int> Map :: get_spawnpoint(){
	return spawnpoint;	
}


