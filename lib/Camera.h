#include <SFML/Graphics.hpp>
#include <vector>

#include "Entity.h"
#include "Ray.h"
#include "World.h"

#ifndef CAMERA_H
#define CAMERA_H

#define PI 3.14159265358979323846f

#define degToRad(angleInDegrees) ((angleInDegrees) * PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / PI)

#define CAMERA_MAX_RAY_STEPS 1000

class Camera : public Entity {
    World* world;
    int nLines;
    float rotation; // radians
    float FOV;      // radians
    std::vector<Ray> rays;
    std::vector<RayHit> rayHits;
    bool hitWall(sf::Vector2i mapPos);

    public:
    Camera(World* world, int nLines=300, int rotation=0, float FOV = PI/2);
    void rotateBy(float rotation);
    void setPosition(sf::Vector2f position);
    const std::vector<Ray>& getRays() const;
    const std::vector<RayHit>& getRayHits() const;
    void captureFrame();
    RayHit getRayMapIntersection(Ray ray);
    const World* getWorld() const;
};


class CameraView {
    const Camera* camera;
    sf::RenderTexture texture;
    int width, height;
    sf::Color mapColor(sf::Vector2i coords);
    public:
    CameraView(const Camera* camera, int width=500, int height=500);
    sf::Sprite getFrame();
};


#endif