/*
 *   Copyright (c) 2021 ishakd00
 *   All rights reserved.
 *   Cpplint made me put this supid copyright header, I swear :'(
 */
#ifndef LIB_VIEW_H_
#define LIB_VIEW_H_

#include <SFML/Graphics.hpp>

class View {
 protected:
    sf::RenderTexture viewTexture;
    float width, height;

 public:
    View(float width, float height);
    virtual sf::Sprite getFrame();
    virtual float getHeight();
    virtual float getWidth();
    virtual void setHeight(float height);
    virtual void setWidth(float width);
    virtual ~View();
};

#endif  // LIB_VIEW_H_
