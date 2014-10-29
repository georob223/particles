#include "welldraw.h"
#include <cmath>
#include <iostream>

welldraw::welldraw(int width, int height)
{
    wellimage.create(width, height,sf::Color::Transparent);
    welltexture.create(width, height);
    wellshade.a=90;
    wellshade.r=45;
    wellshade.b=5;
    wellshade.g=5;
}
welldraw::~welldraw()
{
    ;
}

void welldraw::add(sf::Vector2i wellxy, int strength)
{
    sf::Vector2f distance;
    sf::Vector2u image;
    sf::Vector2u cat;
    image=wellimage.getSize();
    cat.x=wellxy.x;
    cat.y=wellxy.y;

    if(cat.x<0||cat.x>image.x||cat.y<0||cat.y>image.y-1)
        return;
    if(strength<0)
        strength=abs(strength);
    wellcount++;
    for(int i=image.x; i>=0; i--)
    {
        for(int h=image.y-1; h>=0; h--)
        {
            distance.x=wellxy.x-i;
            distance.x*=distance.x;
            distance.y=wellxy.y-h;
            distance.y*=distance.y;
            if(((distance.x+distance.y)<=(strength*strength*10)))
            {
                wellimage.setPixel(i,h,wellshade);
            }
        }
    }

    welltexture.loadFromImage(wellimage);
    wellsprite.setTexture(welltexture);
}

void welldraw::clearwells()
{
    wellcount=0;
    for(int i=wellimage.getSize().x; i>=0; i--)
    {
        for(int h=wellimage.getSize().y-1; h>=0; h--)
        {
            if(wellimage.getPixel(i,h)==wellshade)
                wellimage.setPixel(i,h,sf::Color::Transparent);
        }
    }
    welltexture.loadFromImage(wellimage);
    wellsprite.setTexture(welltexture);
}

