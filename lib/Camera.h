#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

#include "Entity.h"
#include "Ray.h"
#include "World.h"

#ifndef CAMERA_H
#define CAMERA_H

#define PI 3.14159265358979323846f
#define deg90 PI/2

#define degToRad(angleInDegrees) ((angleInDegrees) * PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / PI)

#define CAMERA_MAX_RAY_STEPS 1000

struct Plane {
    float A, B, C;
    float projDenominator;
    Plane();
    Plane(sf::Vector2f direction, sf::Vector2f origin);
    float projDist(sf::Vector2f point) const;
    float f(float x) const;
};

class Camera : public Entity {
    World* world;
    int nLines;
    float rotation; // radians
    float FOV;      // radians
    std::vector<Ray> rays;
    std::vector<RayHit> rayHits;
    sf::Vector2f lookDir;
    sf::Vector2f viewPlaneV;
    Plane viewPlane;
    
    bool hitWall(sf::Vector2i mapPos);

    public:
    Camera(World* world, int nLines=300, int rotation=0, float FOV = PI/2);
    void calcRays();
    void rotateBy(float delta);
    void setRotation(float rotation);
    void setPosition(sf::Vector2f position);
    const std::vector<Ray>& getRays() const;
    const std::vector<RayHit>& getRayHits() const;
    void captureFrame();
    RayHit getRayMapIntersection(Ray ray);
    const World* getWorld() const;
    const Plane& getViewPlane() const;
};


class CameraView {
    const Camera* camera;
    sf::RenderTexture texture;
    int width, height;
    sf::Color mapColor(sf::Vector2i coords, bool shade);
    public:
    CameraView(const Camera* camera, int width=500, int height=500);
    sf::Sprite getFrame();
};


#endif