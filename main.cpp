#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "particle.h"
#include "welldraw.h"


int main()
{
    int width	= 1920;
    int height	= 1080;
    int wellnumber = 25;
    int i = 1;
    float frames=0.0f;
    sf::Clock clock;
    sf::Time time;
    sf::Vector2f gravpos[wellnumber];
    sf::Vector2i merp;
    float pull[wellnumber];
    bool leftdown=false, rightdown=false, rightoff=false, streamparts=false, middle=false;
    sf::RenderWindow window( sf::VideoMode( width, height, 32 ), "Inside the Particle Storm" );
    window.setVerticalSyncEnabled(true);
    sf::Event events;
    sf::Font font;
    if( !font.loadFromFile( "arial.ttf" ) ) return 1;
    sf::Text text( "", font, 10 );
    sf::Text keys("Spacebar=MoreParts WASD=SourceLoc Y=SourceOn U=SourceOff P=ResetSourcePos Arrowkeys=UniGravDir G=ResetAllGrav MdlMouse=StaticGravWell RgtMouse=MouseGravOn LeftMouse=Grav",font, 10);
    //text.setPosition( 10.0f, 10.0f );
    //keys.setPosition(55.0f, 10.0f);

    welldraw Wells( width, height );
    ParticleSystem particleSystem( width, height );
    particleSystem.fuel( 1000 );

    float xpos = width/2.0f;
    float ypos = height/2.0f;
    float xgrv = 0.0f;
    float ygrv = 0.0f;
    gravpos[0].x=0;
    gravpos[0].y=0;
    pull[0]=1;

    while( window.isOpen())
    {
        while(window.pollEvent( events ))
        {


            switch(events.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
            {
                if((events.mouseButton.button==sf::Mouse::Right)&&(rightdown))
                {
                    rightdown=false;
                    rightoff=true;
                    pull[0]=0.0f;
                }
                if((events.mouseButton.button==sf::Mouse::Right)&&(!rightoff))
                {
                    rightdown=true;
                    rightoff=false;
                    pull[0]=30.0f;
                }
                rightoff=false;
                if(events.mouseButton.button==sf::Mouse::Left)
                {
                    leftdown=true;
                    pull[0]=30.0f;
                }
                if(events.mouseButton.button==sf::Mouse::Middle)
                {
                    merp=sf::Mouse::getPosition(window);
                    if(i<wellnumber)
                    {
                        Wells.add(merp,40);
                        gravpos[i].x=merp.x;
                        gravpos[i].y=merp.y;
                        pull[(i++)]=-40.0f;
                    }
                    middle=true;
                }
                break;
            }
             /*case sf::Event::MouseMoved:
                 gravpos[0].x=events.mouseMove.x;
                 gravpos[0].y=events.mouseMove.y;
                 break;
                 */
            case sf::Event::MouseButtonReleased:
                if(events.mouseButton.button==sf::Mouse::Left)
                {
                    leftdown=false;
                    pull[0]=0.0f;
                }
                break;
            case sf::Event::MouseLeft:
                leftdown=false;

            case sf::Event::KeyPressed:
            {

                switch(events.key.code)
                {

                case sf::Keyboard::Space:
                    particleSystem.fuel( 350 );
                    break;
                case sf::Keyboard::Y:
                    streamparts=true;
                    break;
                case sf::Keyboard::U:
                    streamparts=false;
                    break;
                /*case sf::Keyboard::A:
                    particleSystem.setPosition( --xpos, ypos );
                    break;
                case sf::Keyboard::D:
                    particleSystem.setPosition( ++xpos, ypos );
                    break;
                case sf::Keyboard::W:
                    particleSystem.setPosition( xpos, --ypos );
                    break;
                case sf::Keyboard::S:
                    particleSystem.setPosition( xpos, ++ypos );
                    break;*/
                case sf::Keyboard::Left:
                    particleSystem.setGravity( --xgrv * 0.1f, ygrv * 0.1f);
                    break;
                case sf::Keyboard::Right:
                    particleSystem.setGravity( ++xgrv * 0.1f, ygrv * 0.1f );
                    break;
                case sf::Keyboard::Up:
                    particleSystem.setGravity( xgrv * 0.1f, --ygrv * 0.1f );
                    break;
                case sf::Keyboard::Down:
                    particleSystem.setGravity( xgrv * 0.1f, ++ygrv * 0.1f );
                    break;
                case sf::Keyboard::G:
                    Wells.clearwells();
                    particleSystem.setGravity( 0.0f, 0.0f );
                    middle=false;
                    i=1.0f;
                    xgrv=0.0f;
                    ygrv=0.0f;
                    break;
               /* case sf::Keyboard::P:
                    particleSystem.setPosition( width/2.0f, height/2.0f );
                    break;*/
                default:
                    ;
                }
            }
            break;
            default:
                ;
            }
        }
       if(leftdown||rightdown)
        {
            merp=sf::Mouse::getPosition(window);
            gravpos[0].x=merp.x;
            gravpos[0].y=merp.y;
        }
        if(streamparts)
            particleSystem.fuel( 1000 );
        particleSystem.remove();
        if(!leftdown&&!rightdown&&!middle)
            particleSystem.update();
        else
            particleSystem.update(gravpos,pull,i);
        particleSystem.render();

        text.setString( particleSystem.getNumberOfParticlesString() );
        window.clear();
        window.draw(Wells.getSprite());
        window.draw( particleSystem.getSprite() );
        window.draw( text );
        window.draw( keys );
        frames++;
        time=clock.getElapsedTime();
        window.display();
        if(time.asSeconds()>1)
        {
        std::cout<<frames<<std::endl;
        clock.restart();
        frames=0;
        }

    }



    return 0;

}


