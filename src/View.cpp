#include "View.h"

View::View(float width, float height): width(width), height(height){
    viewTexture.create(width, height);
}
float View::getHeight(){
    return height;
}

float View::getWidth(){
    return width;
}

void View::setHeight(float height){
    this->height = height;
}

void View::setWidth(float width){
    this->width = width;
}

sf::Sprite View::getFrame(){
    viewTexture.clear(sf::Color::Black);
    viewTexture.display();
    return sf::Sprite(viewTexture.getTexture());
}

View::~View(){}