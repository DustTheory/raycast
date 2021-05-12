#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <map>

#include "World.h"

#ifndef CAMERA_H
#define CAMERA_H

#define PI 3.14159265358979323846f

#define degToRad(angleInDegrees) ((angleInDegrees) * PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / PI)

#define deg90 PI/2

class Camera {
    const World* world;
    sf::Vector2f position;

    float FOV;
    float rotation;
    int nLines;
    float step;

    inline sf::RectangleShape generateRectangle(int line, int dist, sf::Color color);
    static inline float distToPlane(int mapX, int mapY, int side, sf::Vector2f v, sf::Vector2f u);
    static inline sf::Color mapColor(MapCell cell);

    public:
    Camera(const World* world, float FOV, int nLines);

    void setRotation(float rotation);

    void captureFrame(std::vector<sf::RectangleShape> &lines);

    void prepareRay(sf::Vector2f position, sf::Vector2f direction, sf::Vector2f &deltaDist, sf::Vector2f &sideDist, sf::Vector2i &mapPos, sf::Vector2i &orientation);
    bool hitWall(sf::Vector2i mapPos);
    
    std::tuple<int, int, int> fireRay(sf::Vector2f position, sf::Vector2f direction);
};

class CameraView {
    public:
    CameraView();
    void draw(sf::RenderWindow *window);
};

#endif