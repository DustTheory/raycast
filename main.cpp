#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <unistd.h>


#include "Camera.h"
#include "World.h"
#include "Map.h"
#include "Minimap.h"
#include "Ray.h"


int main(){
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "raycasting_fps");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    sf::VertexArray lines;
    World world("worlds/testWorld.world");
    Camera camera(&world, 300);
    world.addEntity(&camera);
    camera.setPosition({3, 3});
    Minimap minimap(&world, 100, 100);
    CameraView cameraView(&camera);
    while (window->isOpen()){
        window->clear(sf::Color::Black);
        camera.rotateBy(0.2);
        camera.captureFrame();
        window->draw(cameraView.getFrame());
        window->draw(minimap.getFrame());
        window->display();
    }
}
