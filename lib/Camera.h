#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

#include "View.h"
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
    std::vector<RayMapHit> rayHits;
    sf::Vector2f lookDir;
    sf::Vector2f viewPlaneV;
    Plane viewPlane;

    float FOVHeightCorrectionConstant;

    bool hitWall(sf::Vector2i mapPos);

    public:
    Camera(World* world, int nLines=300, int rotation=0, float FOV = PI/2);
    void calcRays();
    void setRotation(float rotation);
    void setPosition(sf::Vector2f position);
    float getFOVHeightCorrectionConstant() const;
    const std::vector<Ray>& getRays() const;
    const std::vector<RayMapHit>& getRayHits() const;
    void captureFrame();
    RayMapHit getRayMapIntersection(Ray ray);
    const World* getWorld() const;
    const Plane& getViewPlane() const;
    const sf::Vector2f& getLookDirection() const;
};


class CameraView : public View {
    const Camera* camera;
    sf::Texture* mapTexture(sf::Vector2i coords, bool shade);
    public:
    CameraView(const Camera* camera, float width, float height);
    sf::Sprite getFrame();
};


#endif