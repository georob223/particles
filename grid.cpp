#include "grid.h"

cell::cell() //No passed items
{
    right_x=0;
    left_x=0;
    right_y=0;
    left_y=0;
    height=0;
    width=0;

}

cell::cell(int x1, int y1, int x2, int y2) //Items passed, rectangle or square
{
    right_x=x1;
    left_x=x2;
    right_y=y1;
    left_y=y2;
    height=left_y-right_y;
    width=left_x-left_y;
}

cell::define_cell_rect(int x1, int y1, int x2, int y2)
{
    right_x=x1;
    left_x=x2;
    right_y=y1;
    left_y=y2;
    height=left_y-right_y;
    width=left_x-left_y;
}


cell::~cell();
cell::std::list<Particle*>objects give_list();
    //void storeParticle(Particle dots) //grabs x,y; stores particle in appropriate cell
    bool is_empty(){if(objects.empty())return true; else return false;}
