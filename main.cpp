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
    Camera camera(&world, 1000, 0, degToRad(60));
    world.addEntity(&camera);
    camera.setPosition({3, 3});
    Minimap minimap(&world, 300, 300);
    float moveSpeed = 0.3;
    float rotateSpeed = degToRad(2);
    CameraView cameraView(&camera, 1000, 1000);
    while (window->isOpen()){
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed){
                char key = event.key.code + 'a';

                if (key == 'w' || key == 'W')
                    camera.moveForward(moveSpeed);
                
                if (key == 'a' || key == 'A')
                    camera.rotateBy(-rotateSpeed);
                
                if (key == 's' || key == 'S')
                    camera.moveForward(-moveSpeed);
                
                if (key == 'd' || key == 'D')
                    camera.rotateBy(rotateSpeed);
            }

            if (event.type == sf::Event::Closed)
                window->close();
        }
        window->clear(sf::Color::Black);
        camera.captureFrame();
        window->draw(cameraView.getFrame());
        sf::Sprite mm = minimap.getFrame();
        window-> draw(mm);
        window->display();
    }
}
