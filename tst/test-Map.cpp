#include "catch.hpp"

#include "Map.hpp"

TEST_CASE("Loading map file", "[Map]"){
	Map map("./maps/json/emptyroom.json");
	REQUIRE(true);
	REQUIRE(map.get_height() == 10);
	REQUIRE(map.get_width() == 10);	
	REQUIRE((map.get_spawnpoint().x == 5 && map.get_spawnpoint().y == 5));
}

TEST_CASE("Reading map coords", "[Map]"){
	Map map("./maps/json/emptyroom.json");
	REQUIRE(map.at_coord(0, 0) == &Map::BLOCK_WALL_BLUE);
	REQUIRE(map.at_coord(1, 0) == &Map::BLOCK_WALL_BLUE);
	REQUIRE(map.at_coord(0, 1) == &Map::BLOCK_WALL_BLUE);
	REQUIRE(map.at_coord(9, 0) == &Map::BLOCK_WALL_BLUE);
	REQUIRE(map.at_coord(0, 9) == &Map::BLOCK_WALL_BLUE);
	REQUIRE(map.at_coord(9, 9) == &Map::BLOCK_WALL_BLUE);
	REQUIRE(map.at_coord(1, 1) == &Map::BLOCK_GROUND);
}

