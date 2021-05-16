/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#include "Camera.h"
#include "World.h"
#include <math.h>

Camera::Camera(World* world, int nLines, int rotation, float FOV): world(world), nLines(nLines), FOV(FOV) {
    FOV = FOV;
    rays.resize(nLines);
    rayHits.resize(nLines);
    setRotation(rotation);
}

void Camera::calcRays() {
    lookDir = sf::Vector2f(sin(rotation), cos(rotation));
    viewPlaneV  = {sin(rotation+deg90), cos(rotation+deg90)};
    viewPlane = Plane(viewPlaneV, position);
    float l = FOVHeightCorrectionConstant = 2*tan(FOV/2);
    float step = l/nLines;
    float segmetnOffset = -tan(FOV/2);
    for (int i = 0; i < static_cast<int>(rays.size()); i++) {
        sf::Vector2f direction = lookDir + segmetnOffset*viewPlaneV;
        rays[i] = Ray(getPosition(), direction);
        segmetnOffset += step;
    }
}

void Camera::setRotation(float rotation) {
    this->rotation = rotation;
    calcRays();
}

void Camera::setPosition(sf::Vector2f position) {
    this->position = position;
    calcRays();
}

const sf::Vector2f& Camera::getLookDirection() const {
    return lookDir;
}

const std::vector<Ray>& Camera::getRays() const {
    return rays;
}

const std::vector<RayMapHit>& Camera::getRayHits() const {
    return rayHits;
}


void Camera::captureFrame() {
    for (int i = 0; i < static_cast<int>(rays.size()); i++)
        rayHits[i] = getRayMapIntersection(rays.at(i));
}

bool Camera::hitWall(sf::Vector2i mapPos) {
    if (world->map.isOutOfBounds(mapPos.x, mapPos.y))
        return true;
    return world->map.atCoords(mapPos.x, mapPos.y) != MapCell::EmptyCell;
}

RayMapHit Camera::getRayMapIntersection(Ray ray) {
    sf::Vector2i mapPos = { static_cast<int>(ray.origin.x),
                            static_cast<int>(ray.origin.y)
    };
    sf::Vector2f pos = ray.origin;
    bool side = ray.mapStep(pos);
    for (int step = 0; step < CAMERA_MAX_RAY_STEPS; step++) {
        if (side)
            mapPos = {  static_cast<int>(floor(pos.x)),
                        static_cast<int>(pos.y - (ray.direction.y < 0))
            };
        else
            mapPos = {  static_cast<int>(pos.x - (ray.direction.x < 0)),
                        static_cast<int>(ceil(pos.y) - 1)
            };
        if (hitWall(mapPos))
            break;
        side = ray.mapStep(pos);
    }
    return { pos, mapPos, side };
}

const World* Camera::getWorld() const {
    return world;
}


CameraView::CameraView(const Camera* camera, float width, float height): View(width, height), camera(camera) {
}

float Camera::getFOVHeightCorrectionConstant() const {
    return FOVHeightCorrectionConstant;
}

const sf::IntRect& CameraView::getTxRectForCellAt(int i, int j) {
    return camera->getWorld()->map.atCoords(i, j).getTxRect();
}

sf::Sprite CameraView::getFrame() {
    viewTexture.clear(sf::Color::Black);

    sf::RectangleShape floorRect, ceilingRect;
    floorRect.setFillColor(sf::Color(30, 30, 30));
    ceilingRect.setFillColor(sf::Color(140, 190, 213));
    floorRect.setSize({width, height/2});
    ceilingRect.setSize({width, height/2});
    floorRect.setPosition({0, height/2});

    viewTexture.draw(floorRect);
    viewTexture.draw(ceilingRect);

    const std::vector<Ray> &rays = camera->getRays();
    const std::vector<RayMapHit> &rayHits = camera->getRayHits();

    float rectWidth = width/static_cast<float>(rays.size());
    for (int i = 0; i < static_cast<int>(rays.size()); i++) {
        float baseHeight = 2*this->height/
                            camera->getFOVHeightCorrectionConstant();
        float height = baseHeight/
                        camera->getViewPlane().projDist(rayHits[i].pos);
        sf::RectangleShape rectangle;
        sf::RectangleShape rectOverlay;
        rectangle.setPosition({rectWidth*i, this->height/2 - height/2});
        rectOverlay.setPosition({rectWidth*i, this->height/2 - height/2});
        rectangle.setSize({rectWidth, height});
        rectOverlay.setSize({rectWidth, height});
        rectangle.setTexture(&MapCell::mapTexture);

        rectOverlay.setFillColor(sf::Color(0, 0, 0, rayHits[i].side ? 100 : 0));
        float textureXOffset = rayHits[i].side == 1 ?
                                rayHits[i].pos.x - floor(rayHits[i].pos.x) :
                                rayHits[i].pos.y - floor(rayHits[i].pos.y);
        const sf::IntRect& txRect = getTxRectForCellAt(rayHits[i].mapPos.x,
                                                        rayHits[i].mapPos.y);

        float x = txRect.left + static_cast<int>(textureXOffset*txRect.width);
        rectangle.setTextureRect({ (float)x, txRect.top, 1, txRect.height });
        viewTexture.draw(rectangle);
        viewTexture.draw(rectOverlay);
    }

    viewTexture.display();
    return sf::Sprite(viewTexture.getTexture());
}

const Plane& Camera::getViewPlane() const {
    return viewPlane;
}

Plane::Plane(sf::Vector2f direction, sf::Vector2f origin) {
    A = direction.y/direction.x;
    B = -1;
    C =  origin.y - A*origin.x;
    projDenominator = sqrt(A*A + B*B);
}

float Plane::projDist(sf::Vector2f point) const {
    return abs((A*point.x + B*point.y + C)/projDenominator);
}
float Plane::f(float x) const {
    return A*x + C;
}

Plane::Plane() {}
