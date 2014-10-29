#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class welldraw
{
public:
    welldraw(int width, int height);
    ~welldraw();
    void add(sf::Vector2i wellxy, int strength);
    void clearwells();

    int wellnumber() { return wellcount; }
    sf::Sprite& getSprite() { return wellsprite; }

private:
    sf::Image wellimage;
    sf::Texture welltexture;
    sf::Sprite wellsprite;
    sf::Color wellshade;
    int wellcount;

};

