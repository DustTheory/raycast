#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <unistd.h>
#include <fstream>

#include "Camera.h"
#include "World.h"
#include "Map.h"
#include "Minimap.h"
#include "Ray.h"
#include "HUD.h"
#include "Player.h"

#include "json.hpp"

using json = nlohmann::json;

int main(){

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "raycasting_fps");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    sf::VertexArray lines;
    World world("worlds/testWorld.json");
    Player player(&world, {3, 3}, 0);

    while (window->isOpen()){
        sf::Event event;
        while (window->pollEvent(event))
        {
            player.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window->close();
        }
        window->clear(sf::Color::Black);
        window->draw(player.playerView.getFrame());
        window->display();
    }
}
