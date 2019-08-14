#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include "json.hpp"

#include "Map.hpp"

#include <iostream>
#include <iomanip>

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

#define N_BASE_BLOCK_TYPES 2

Block Map::BLOCK_GROUND = Block(sf::Color::Transparent, false, false);
Block Map::BLOCK_WALL_BLUE = Block(sf::Color::Blue);

std::vector<Block*> Map::base_block_types = std::vector<Block*>{
	&BLOCK_GROUND,
	&BLOCK_WALL_BLUE
};

Map :: Map() : h(0), w(0), spawnpoint({0, 0}) {
	block_types.assign(base_block_types.begin(), base_block_types.end());
}

Map :: Map(std::string map_filepath){
	block_types.assign(base_block_types.begin(), base_block_types.end());
	load_map_file(map_filepath);
}
	
void Map :: load_map_file(std::string map_filepath){
		std::ifstream input_stream(map_filepath);
		std::string tmp( (std::istreambuf_iterator<char>(input_stream) ),
						 (std::istreambuf_iterator<char>()             ) );	
		json map_json = json::parse(tmp);
		h = map_json["height"];
		w = map_json["width"];

		map.assign(map_json["map"].begin(), map_json["map"].end());
	
		spawnpoint = {map_json["spawnpoint_x"], map_json["spawnpoint_y"]};

	}

int Map :: get_height(){
	return h;
}

int Map :: get_width(){
	return w;
}


Block* Map :: at_coord(int x, int y){
	return block_types[map[y*w+x - ((x == y) ? 0 : 1)]];
}

Block* Map :: at_pos(int p){
	return block_types[map[p]];
}

sf::Vector2<int> Map :: get_spawnpoint(){
	return spawnpoint;	
}

