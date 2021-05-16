/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#include <vector>
#include <SFML/Graphics.hpp>

#include "World.h"
#include "Player.h"

int main() {
    static const std::vector<sf::VideoMode> &videoModes =
                                            sf::VideoMode::getFullscreenModes();
    sf::RenderWindow *window = new sf::RenderWindow(
        videoModes[0],
        "raycasting_fps",
        sf::Style::Fullscreen);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    sf::VertexArray lines;
    World world("worlds/testWorld.json");
    Player player(window, &world, {3, 3}, 0);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            player.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window->close();
        }
        window->clear(sf::Color::Black);
        window->draw(player.playerView.getFrame());
        window->display();
    }
}
