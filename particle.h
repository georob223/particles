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
};

typedef std::list<Particle*>::iterator ParticleIterator;

class cell
{
public:
    cell();
    cell(float x0, float y0, float x4, float y4);
    ~cell();
    void define_cell(float x0, float y0, float x4, float y4); //Generates a cell
    int getWidth(){return width;}
    int getHeight(){return height;}
    std::list<Particle*>& pop_list();
    void push_list( std::list<Particle*> & updated );
    int insertParticle(Particle* dot); //stores a particle
    bool is_empty(){if(objects.empty())return true; else return false;}
    int capacity(); //gives back max number of storeable pixels
    int amount(); //gives number of currently stored particles
    void delcell(); //erases cell and particles.
    bool range_check(float x, float y); //checks if a particle is valid.
    ParticleIterator begin(){ return objects.begin(); }
    ParticleIterator end(){ return objects.end(); }
    ParticleIterator erase( ParticleIterator ut){ return objects.erase( ut ); }
private:
    int width, height;
    float x_0, y_0;
    float x_4,  y_4;
    std::list<Particle*>objects;
};
typedef std::list<cell*>::iterator CellIterator;
/* grid should store cells
grid should sort cells
grid should determine where particles go
grid should maintain only occupied cells
grid should give lists of local cells to
check for collides
grid should give access to individual particles
grid should self create cells when needed
    cases for creation:
        first particle passed
        cells exist
        cell full
        cell empty
        cells exist, new particle is out side of ranges
        particle is out of range
        */

class grid
{
public:
    grid();
    grid(int x, int y);
    void make_grid(int x, int y);
    void insert_cell( Particle * object );
    ~grid();
    std::string status();
    CellIterator begin();
    CellIterator end();
    CellIterator is_empty(CellIterator cells);
    void range_cells();
    int size();
private:
    std::list<cell*>griddle;
    std::list<Particle*>fire;
    int grid_x, grid_y;
};

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
	grid noms;
};

#endif
