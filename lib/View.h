#include <SFML/Graphics.hpp>

#ifndef VIEW_H
#define VIEW_H


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

#endif