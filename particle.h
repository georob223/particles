#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <list>
#include <cmath>
#include <iostream>

namespace Shape { enum { CIRCLE, SQUARE }; }
struct link;

struct Particle
{
	sf::Vector2f pos; // Position
	sf::Vector2f vel; // Velocity
	sf::Color color;  // RGBA
	std::list<link> neighbor_register;
};

struct link
{
    float length;
    Particle * neighbor;
};

typedef std::list<Particle*>::iterator ParticleIterator;

class ParticleSystem
{
public:
	ParticleSystem( int width, int height );
	~ParticleSystem();

	void fuel( unsigned int particles ); // Adds new particles to m_particles
	void update(); // Updates position, velocity and opacity of all particles
	sf::Vector2f grav_well(sf::Vector2f well, sf::Vector2f partpos, float strength);
	void update(sf::Vector2f * local_well, float * pull, int wells);
	void delrandparts( int number ); //Deletes random particles from the list
	void render(); // Renders all particles onto m_image
	void remove(); // Removes all particles from m_image

	//void setPosition( float x, float y ) { m_position.x = x; m_position.y = y;}
	void setGravity( float x, float y ) { m_gravity.x = x; m_gravity.y = y; }
	void setParticleSpeed( float speed ) { m_particleSpeed = speed; }
	void setDissolve( bool enable ) { m_dissolve = enable; }
	void setDissolutionRate( unsigned char rate ) { m_dissolutionRate = rate; }
	void setShape( unsigned char shape ) { m_shape = shape; }
    void particle_hit_loop();
    bool pixel_collision(int x, int y, int x1, int y1);
    void change_position(ParticleIterator first, ParticleIterator second);

	int getNumberOfParticles() { return m_particles.size(); }
	std::string getNumberOfParticlesString();
	sf::Sprite& getSprite() { return m_sprite; }

private:
	sf::Vector2f	m_position [2500];	// Particle origin (pixel co-ordinates)
	sf::Vector2f	m_gravity;	// Affects particle velocities
	//sf::Randomizer	m_randomizer;	// Randomizes particle velocities
	sf::Clock	m_clock;	// Used to scale particle motion
	sf::Color	m_transparent;	// sf::Color( 0, 0, 0, 0 )
	sf::Image m_image;	// See render() and remove()
	sf::Texture m_texture;
	sf::Sprite	m_sprite;	// Connected to m_image
	float		m_particleSpeed;// Pixels per second (at most)
	bool		m_dissolve;	// Dissolution enabled?
	unsigned char	m_dissolutionRate;
	unsigned char	m_shape;

	std::list<Particle*> m_particles;
};

#endif
