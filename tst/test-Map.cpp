#include "catch.hpp"

#include "Map.hpp"

TEST_CASE("Loading map file"){
	Map map("./maps/json/emptyroom.json");
	REQUIRE(true);
	REQUIRE(map.get_height() == 10);
	REQUIRE(map.get_width() == 10);	
	REQUIRE((map.get_spawnpoint().x == 5 && map.get_spawnpoint().y == 5));

}

