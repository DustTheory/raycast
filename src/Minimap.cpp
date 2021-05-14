#include <type_traits>
#include "Entity.h"
#include "Camera.h"
#include "Minimap.h"

Minimap::Minimap(const World* world, int width, int height): world(world), width(width), height(height){
    cellSide = std::min(width, height)/std::max(world->map.getMapHeight(), world->map.getMapWidth());
    texture.create(width, height);
}

std::map<MapCell, sf::Color> getMinimapColorMap(){
    std::map<MapCell, sf::Color> colorMap;
    colorMap[MapCell::EmptyCell] = sf::Color::Black;
    colorMap[MapCell::Wall1] = sf::Color::Red;
    colorMap[MapCell::Wall2] = sf::Color::Green;
    colorMap[MapCell::Wall3] = sf::Color::Blue;
    colorMap[MapCell::Wall4] = sf::Color::White;
    colorMap[MapCell::Wall5] = sf::Color::Yellow;
    return colorMap;
}


sf::Color Minimap::mapColor(MapCell cell){
    static std::map<MapCell, sf::Color> colorMap = getMinimapColorMap();
    return colorMap[cell];
}


sf::CircleShape entityCircle(sf::Vector2f position, float radius=5, sf::Color color=sf::Color::Magenta){
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setPosition(position-sf::Vector2f(radius, radius));
    return circle;
}

sf::Sprite Minimap::getFrame(){
    texture.clear(sf::Color::Black);
    for(int i = 0; i < world->map.getMapHeight(); i++){
        for(int j = 0; j < world->map.getMapWidth(); j++){
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(cellSide, cellSide));
           /*  rectangle.setOutlineThickness(1);
            rectangle.setOutlineColor(sf::Color::Black); */
            rectangle.setFillColor(mapColor(world->map.atCoords(i, j)));
            rectangle.setPosition(i*cellSide, j*cellSide);
            texture.draw(rectangle);
        }
    }

    for(Entity* entity : world->getEntities()){
        Camera* cameraEntity = dynamic_cast<Camera *>(entity);
        if(cameraEntity){
            drawCamera(cameraEntity);
        }else{
            texture.draw(entityCircle(entity->getPosition()*cellSide));
        }
    }

    texture.display();
    return sf::Sprite(texture.getTexture());
}

void Minimap::drawCamera(Camera* camera){
    float dotRadius = 5;
    const std::vector<Ray>& cameraRays = camera->getRays();
    const std::vector<RayHit>& cameraRayHits = camera->getRayHits();
    sf::VertexArray rays(sf::TrianglesStrip, cameraRays.size()*2);
    sf::Color raysColor = sf::Color(255, 255, 255, 100);
    for(int i = 0; i < (int)cameraRays.size(); i++){
        rays[i*2].position = cameraRays[i].origin*cellSide;
        rays[i*2+1].position = cameraRayHits[i].pos*cellSide;
        rays[i*2+1].color = rays[i*2].color = raysColor;
    }

    sf::VertexArray viewPlaneLine(sf::Lines, 2);
    const Plane& viewPlane = camera->getViewPlane();
    viewPlaneLine[0].position = sf::Vector2f(0, viewPlane.f(0))*cellSide;
    viewPlaneLine[1].position = sf::Vector2f((float)width,viewPlane.f((float)width))*cellSide;
    texture.draw(viewPlaneLine);
    texture.draw(rays);
    texture.draw(entityCircle(camera->getPosition()*cellSide, dotRadius));
}
