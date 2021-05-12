#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <unistd.h>


#include "Camera.h"
#include "World.h"
#include "Map.h"


int main(){
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "raycasting_fps");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    sf::VertexArray lines;
    Map map = Map();
    World world = World(map);
    Camera camera = Camera(&world, 90, 300);
    
    float rot = 0;
    while (window->isOpen()){
        window->clear(sf::Color::Black);
        std::vector<sf::RectangleShape> v;
        camera.captureFrame(v);
        for(sf::RectangleShape &rect : v)
            window->draw(rect);
        camera.setRotation(rot+=1);
        window->display();
    }
}
