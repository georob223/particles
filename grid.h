#include "particle.h"
#include <list>

class cell
{
public:
    cell();
    cell(int x1, int y1, int x2, int y2);
    ~cell();
    define_cell(int x1, int y1, int x2, int y2);
    int getWidth(){return width;}
    int getHeight(){return height;}
    void cellmake(); //generates cell
    std::list<Particle*> give_list();
    //void storeParticle(Particle dots) //grabs x,y; stores particle in appropriate cell
    bool is_empty(){if(objects.empty())return true; else return false;}
private:
    int width, height;
    int right_x, right_y;
    int left_x,  left_y;
    std::list<Particle*>objects;
};


class grid : public cell
{
public:
    grid();
    grid(int x, int y);
    ~grid();
    int compare_cells(cell cell_1, cell cell_2, cell cell_3);
private:
    std::list<cell>grider;
    int grid_x, grid_y;
};
