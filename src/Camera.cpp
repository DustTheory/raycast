#include "Camera.h"

inline float Camera::distToPlane(int mapX, int mapY, int side, sf::Vector2f v, sf::Vector2f u){
    return sqrt((v.x-mapX)*(v.x-mapX) + (v.y-mapY)*(v.y-mapY));
    /* int stepX = v.x < 0 ? -1 : 0;
    int stepY = v.y < 0 ? -1 : 0;
    if (side == 0)
        return (mapX - u.x + (1 - stepX) / 2) / v.x;
    return (mapY - u.x + (1 - stepY) / 2) / v.y; */
}

void Camera::captureFrame(std::vector<sf::RectangleShape> &lines)
{
    lines.clear();
    sf::Vector2f lookDir = {cos(rotation), sin(rotation)};
    sf::Vector2f planeVector = {cos(rotation + deg90), sin(rotation + deg90)};
    sf::Vector2f u = position + lookDir * (1 / tan(FOV));

    int mapX, mapY, side;
    float currentOffset = 1;

    for (int i = 0; i < nLines; i++)
    {
        sf::Vector2f v = u + planeVector * currentOffset;
        std::tie(mapX, mapY, side) = fireRay(position, lookDir);
        float dist = distToPlane(mapX, mapY, side, position, u);
        printf("%d %d\n", mapX, mapY);
        sf::Color color;
        if(world->map.isOutOfBounds(mapX, mapY))
            color = mapColor(MapCell::Wall1);
        else
            color = mapColor(world->map.atCoords(mapX, mapY));
        lines.push_back(generateRectangle(i, dist, color));
        currentOffset -= step;
    }
}

void Camera::prepareRay(sf::Vector2f position, sf::Vector2f direction, sf::Vector2f &deltaDist, sf::Vector2f &sideDist, sf::Vector2i &mapPos, sf::Vector2i &orientation){
    mapPos = {(int)position.x, (int)position.y};
    
    orientation = {
        direction.x < 0 ? -1 : 1,
        direction.y < 0 ? -1 : 1
    };

    if(direction.x == 0)
        deltaDist = {0, 1};
    else if(direction.y == 0)
        deltaDist = {1, 0};
    else
        deltaDist = { abs(1.0f/direction.x), abs(1.0f/direction.y) };
    printf("%f %f", deltaDist.x, deltaDist.y);

    sideDist = {
        (orientation.x == -1 ? (position.x-mapPos.x) : (1.0f-position.x + mapPos.x))*deltaDist.x,
        (orientation.y == -1 ? (position.y-mapPos.y) : (1.0f-position.y + mapPos.y))*deltaDist.y
    };        
}

bool Camera::hitWall(sf::Vector2i mapPos){
    if(world->map.isOutOfBounds(mapPos.x, mapPos.y))
        return true;
    return world->map.atCoords(mapPos.x, mapPos.y) != MapCell::EmptyCell;
}

std::tuple<int, int, int> Camera::fireRay(sf::Vector2f position, sf::Vector2f direction){
    sf::Vector2f deltaDist, sideDist;
    sf::Vector2i mapPos, orientation;
    prepareRay(position, direction, deltaDist, sideDist, mapPos, orientation);   
    bool side = 0;

    while(!hitWall(mapPos)){
        if(sideDist.x < sideDist.y){
            sideDist.x += deltaDist.x;
            mapPos.x += orientation.x;
            side = 0;
        }else{
            sideDist.y += deltaDist.y;
            mapPos.y += orientation.y;
            side = 1;
        }
    }
    return {mapPos.x, mapPos.y, side};
}


Camera::Camera(const World *world, float FOV, int nLines) : world(world), position({20, 20}), nLines(nLines), rotation(0)
{
    this->FOV = degToRad(FOV) / 2;
    step = 2.0 / nLines;
}

void Camera::setRotation(float rotation)
{
    this->rotation = degToRad(rotation);
}

inline sf::RectangleShape Camera::generateRectangle(int line, int dist, sf::Color color){
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(500 / nLines, dist * 100));
        rectangle.setFillColor(color);
        rectangle.setPosition(line * 500 / nLines, 20);
        return rectangle;
}

sf::Color Camera::mapColor(MapCell cell)
{
    switch ((int)cell)
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
