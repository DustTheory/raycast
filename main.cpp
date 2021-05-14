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
    Camera camera(&world, 300, 0, degToRad(100));
    world.addEntity(&camera);
    camera.setPosition({3, 3});
    camera.setRotation(degToRad(90));
    Minimap minimap(&world, 100, 100);
    CameraView cameraView(&camera);
    while (window->isOpen()){
        window->clear(sf::Color::Black);
        camera.captureFrame();
        window->draw(cameraView.getFrame());
        window->draw(minimap.getFrame());
        camera.rotateBy(degToRad(-0.1));
        window->display();
    }
}
