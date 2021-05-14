#include "Camera.h"
#include "World.h"
#include <math.h>

Camera::Camera(World* world, int nLines, int rotation, float FOV): world(world), nLines(nLines), FOV(FOV){
    sf::Vector2f lookDir = {0, 1};
    sf::Vector2f vPlane  = {1, 0};

    float angleStep = FOV/nLines; 
    float angle = -FOV/2;
    
    rayHits.resize(nLines);

    for(int i = 0; i < nLines; i++){
        sf::Vector2f direction = lookDir + tan(angle)*vPlane;
        rays.emplace_back(getPosition(), direction);
        angle += angleStep;
    }
    rotateBy(rotation);
}

void Camera::rotateBy(float rotation){
    sf::Transform rotationTransform;
    rotationTransform.rotate(rotation);
    this->rotation = degToRad(rotation);
    for(Ray &r :  rays)
        r.direction = rotationTransform.transformPoint(r.direction);
}

void Camera::setPosition(sf::Vector2f position){
    this->position = position;
    for(Ray& ray : rays)
        ray.origin = getPosition();
}

const std::vector<Ray>& Camera::getRays() const{
    return rays;
}

const std::vector<RayHit>& Camera::getRayHits() const{ 
    return rayHits;
}


void Camera::captureFrame(){
    for(int i = 0; i < (int)rays.size(); i++)
        rayHits[i] = getRayMapIntersection(rays.at(i));
}

bool Camera::hitWall(sf::Vector2i mapPos){
    if(world->map.isOutOfBounds(mapPos.x, mapPos.y))
        return true;
    return world->map.atCoords(mapPos.x, mapPos.y) != MapCell::EmptyCell;
}

RayHit Camera::getRayMapIntersection(Ray ray){
    sf::Vector2i mapPos = {(int)ray.origin.x, (int)ray.origin.y};
    sf::Vector2f pos = ray.origin;
    bool side = ray.mapStep(pos);
    for(int step = 0; step < CAMERA_MAX_RAY_STEPS; step++){
        if(side == 0 && ray.direction.x < 0)
            mapPos = { (int)pos.x - 1, (int)ceil(pos.y) - 1 };
        else if(side == 0 && ray.direction.x >= 0)
            mapPos = { (int)pos.x, (int)ceil(pos.y) - 1 };
        else if(side == 1 && ray.direction.y >= 0)
            mapPos = { (int)floor(pos.x), (int)pos.y };
        else if(side == 1 && ray.direction.y < 0)
            mapPos = { (int)floor(pos.x), (int)pos.y - 1};
        if(hitWall(mapPos))
            break;
        side = ray.mapStep(pos);
    }
    return {pos, mapPos, side};
}

const World* Camera::getWorld() const{
    return world;
}

CameraView::CameraView(const Camera* camera, int width, int height): camera(camera), width(width), height(height){
    texture.create(width, height);
}

sf::Color CameraView::mapColor(sf::Vector2i coords){
    MapCell cell;
    if(camera->getWorld()->map.isOutOfBounds(coords.x, coords.y))
        cell = MapCell::Wall1;
    else
        cell = camera->getWorld()->map.atCoords(coords.x, coords.y);
    switch ((int) cell)
    {
    case 1:
        return sf::Color::Red;
    case 2:
        return sf::Color::Green;
    case 3:
        return sf::Color::Blue;
    case 4:
        return sf::Color::White;
    default:
        return sf::Color::Yellow;
    }
    return sf::Color::Yellow;
}

inline float dist(sf::Vector2f a, sf::Vector2f b){
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

inline sf::RectangleShape generateRectangle(sf::Vector2f position, sf::Vector2f size, sf::Color color){
        sf::RectangleShape rectangle;
        rectangle.setSize(size);
        rectangle.setFillColor(color);
        rectangle.setPosition(position);
        return rectangle;
}

sf::Sprite CameraView::getFrame(){
    texture.clear(sf::Color::Black);

    const std::vector<Ray> &rays = camera->getRays();
    const std::vector<RayHit> &rayHits = camera->getRayHits();
    
    float rectWidth = width/(float)rays.size();
    for(int i = 0; i < (int)rays.size(); i++){
        float height = 100.0/dist(rays[i].origin, rayHits[i].pos);
        texture.draw(generateRectangle({rectWidth*i, 200-height}, {rectWidth, height}, mapColor(rayHits[i].mapPos)));
    }
    
    texture.display();
    return sf::Sprite(texture.getTexture());
}

