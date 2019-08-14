#include <SFML/Graphics.hpp>

#ifndef MAP_H
#define MAP_H

	struct Block{
		sf::Color color;
		bool visible, colliding;
		Block();
		Block(sf::Color _color, bool _visible = true, bool _colliding = true);
	};

	class Map{
		private:
		int h, w;
		std::vector<uint8_t> map;
		sf::Vector2<int> spawnpoint;
		std::vector<Block*> block_types;
		public:
		Map();
		Map(std::string map_filepath);
		void load_map_file(std::string map_filepath);
		int get_height();
		int get_width();
		sf::Vector2<int> get_spawnpoint();
		Block* at_coord(int x, int y);
		Block* at_pos(int p);	
		static Block BLOCK_GROUND;
		static Block BLOCK_WALL_BLUE;
		static std::vector<Block*> base_block_types;

	};

#endif
