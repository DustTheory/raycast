#include <Ray.h>
#include <stdexcept>
#include <limits>
#include <math.h>

float euclidianDistNoRoot(sf::Vector2f v1, sf::Vector2f v2){
    return (v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y);
}

Ray::Ray(sf::Vector2f origin, sf::Vector2f direction): origin(origin), direction(direction){}
Ray::Ray(){}

#define INF std::numeric_limits<float>::infinity() 

float Ray::yOnRay(float x){
    if(direction.x == 0)
        throw std::exception();
    float k = direction.y/direction.x;
    float n = origin.y - origin.x*k;
    return k*x + n;
}

float Ray::xOnRay(float y){
    if(direction.x == 0 || direction.y == 0)
        throw std::exception();
    float k = direction.y/direction.x;
    float n = origin.y - origin.x*k;
    return (y - n)/k;
}


// 0 - hit vertical line
// 1 - hit horizontal line
bool Ray::mapStep(sf::Vector2f &position){
    int nextX = direction.x > 0 ? (int) position.x + 1 : ceil(position.x - 1);
    int nextY = direction.y > 0 ? (int) position.y + 1 : ceil(position.y - 1);

    if(direction.y == 0 && direction.x == 0){
        return 0;
    }
    else if(direction.x == 0 && direction.y != 0){
        position = { origin.x, (float)nextY };
        return 1;
    }else if(direction.y == 0 && direction.x != 0){
        position = { (float)nextX, origin.y };
        return 0;
    }
    sf::Vector2f nextVertical(nextX, yOnRay(nextX) );
    sf::Vector2f nextHorizontal( xOnRay(nextY), nextY);
    if(euclidianDistNoRoot(position, nextVertical) < euclidianDistNoRoot(position, nextHorizontal)){
        position = nextVertical;
        return 0;
    }
    position = nextHorizontal;
    return 1;
}