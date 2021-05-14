#include "Camera.h"
#include "World.h"
#include <math.h>

Camera::Camera(World* world, int nLines, int rotation, float FOV): world(world), nLines(nLines), FOV(FOV){
    FOV = FOV;
    rays.resize(nLines);
    rayHits.resize(nLines);
    setRotation(rotation);
}

void Camera::rotateBy(float delta){
    setRotation(rotation+delta);
}

void Camera::calcRays(){
    lookDir = sf::Vector2f(sin(rotation), cos(rotation));
    viewPlaneV  = {sin(rotation+deg90), cos(rotation+deg90)};
    viewPlane = Plane(viewPlaneV, position);
    float l = FOVHeightCorrectionConstant = 2*tan(FOV/2);
    float step = l/nLines;
    float segmetnOffset = -tan(FOV/2);
    for(int i = 0; i < rays.size(); i++){
        sf::Vector2f direction = lookDir + segmetnOffset*viewPlaneV;
        rays[i] = Ray(getPosition(), direction, atan(segmetnOffset));
        segmetnOffset += step;
    }
}

void Camera::setRotation(float rotation){
    this->rotation = rotation;
    calcRays();
}

void Camera::setPosition(sf::Vector2f position){
    this->position = position;
    calcRays();
}

void Camera::moveForward(float moveSpeed){
    setPosition(getPosition()+lookDir*moveSpeed);
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
        if(side)
            mapPos = { (int)floor(pos.x), (int)pos.y - (ray.direction.y < 0)};
        else
            mapPos = { (int)pos.x - (ray.direction.x < 0), (int)ceil(pos.y) - 1 };
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

std::map<MapCell, sf::Color> getCameraColorMap(){
    std::map<MapCell, sf::Color> colorMap;
    colorMap[MapCell::EmptyCell] = sf::Color::Magenta;
    colorMap[MapCell::Wall1] = sf::Color::Red;
    colorMap[MapCell::Wall2] = sf::Color::Green;
    colorMap[MapCell::Wall3] = sf::Color::Blue;
    colorMap[MapCell::Wall4] = sf::Color::White;
    colorMap[MapCell::Wall5] = sf::Color::Yellow;
    return colorMap;
}

sf::Color CameraView::mapColor(sf::Vector2i coords, bool shade){
    static std::map<MapCell, sf::Color> colorMap = getCameraColorMap();
    MapCell cell;
    if(camera->getWorld()->map.isOutOfBounds(coords.x, coords.y))
        cell = MapCell::Wall1;
    else
        cell = camera->getWorld()->map.atCoords(coords.x, coords.y);
    sf::Color c = colorMap[cell];
    float multiplier = shade ? 0.5 : 1;
    return  { (sf::Uint8)c.r*multiplier, (sf::Uint8)c.g*multiplier, (sf::Uint8)c.b*multiplier };
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

float Camera::getFOVHeightCorrectionConstant() const{
    return FOVHeightCorrectionConstant;
}

sf::Sprite CameraView::getFrame(){
    texture.clear(sf::Color::Black);

    const std::vector<Ray> &rays = camera->getRays();
    const std::vector<RayHit> &rayHits = camera->getRayHits();
    
    float rectWidth = width/(float)rays.size();
    for(int i = 0; i < (int)rays.size(); i++){
        float height = this->height/camera->getFOVHeightCorrectionConstant()/camera->getViewPlane().projDist(rayHits[i].pos); 
        texture.draw(generateRectangle({rectWidth*i, this->height/2 - height/2}, {rectWidth, height}, mapColor(rayHits[i].mapPos, rayHits[i].side)));
    }
    
    texture.display();
    return sf::Sprite(texture.getTexture());
}

const Plane& Camera::getViewPlane() const {
    return viewPlane;
}

Plane::Plane(sf::Vector2f direction, sf::Vector2f origin){
    A = direction.y/direction.x;
    B = -1;
    C =  origin.y - A*origin.x;
    projDenominator = sqrt(A*A + B*B);
}

float Plane::projDist(sf::Vector2f point) const{
    return abs((A*point.x + B*point.y + C)/projDenominator);
}
float Plane::f(float x) const{
    return A*x + C;
}

Plane::Plane(){}