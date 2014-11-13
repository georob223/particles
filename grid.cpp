#include "particle.h"

/* Begin Cell definitions */
cell::cell() //No passed items
{
    x_4=0;
    x_0=0;
    y_4=0;
    y_0=0;
    width=0;
    height=0;
}

//x0, y0 ==left and top most corner x4, y4 == right and bottommost corner
cell::cell(float x0, float y0, float x4, float y4) //Items passed, rectangle.
{
    x_4=x4;
    x_0=x0;
    y_4=y4;
    y_0=y0;
    height=x_4-x_0;
    width=y_4-y_0;
}

void cell::define_cell(float x0, float y0, float x4, float y4) //Items passed, rectangle.
{
    x_4=x4;
    x_0=x0;
    y_4=y4;
    y_0=y0;
    height=x_4-x_0;
    width=y_4-y_0;
}

int cell::capacity() //gives back max number of storeable pixels
{
    return width*height;
}

int cell::amount()//gives number of currently stored particles
{
    return objects.size();
}
cell::~cell()
{
    objects.clear();

}
std::list<Particle*>& cell::pop_list()
{
    return objects;
}
void cell::push_list( std::list<Particle*> & updated )
{
    objects.merge(updated);
}
int cell::insertParticle(Particle* dot) //stores a particle
{

        if(range_check((dot->pos.x),(dot->pos.y)))
        {
            objects.push_front(dot);
            return 0;
        }
        else
        {
        return 2; //not in range
        }

}

void cell::delcell() //erases cell and particles.
{
    this->~cell();
    return;
}

bool cell::range_check(float x, float y)
{
    bool xe=false;
    bool ye=false;
    if(x<x_4&&x>=x_0)
        xe=true;
    if(y<y_4&&y>=y_0)
        ye=true;
    if(xe&&ye)
    {
        return true;
    }

    return false;
}
 /* End Cell definitions */

 /* Begin Grid definitions */

grid::grid()
{
    grid_x=0;
    grid_y=0;
}

grid::grid(int x, int y)
{
    grid_x=x;
    grid_y=y;

}

void grid::make_grid(int x, int y)
{
    grid_x=x;
    grid_y=y;
}

grid::~grid()
{

}
CellIterator grid::is_empty(CellIterator cells)
{
    if((*cells)->is_empty())
    return griddle.erase(cells);
    return cells;
}

CellIterator grid::begin()
{
    return griddle.begin();
}

CellIterator grid::end()
{
    return griddle.end();
}

void grid::insert_cell( Particle* object )
{
    cell* funcell;
    funcell=new cell;
    int val=-1;
    if(griddle.empty())
    {
        funcell->define_cell(object->pos.x-0.5f, object->pos.y-0.5f, object->pos.x+25.5f, object->pos.y+25.5f);
        funcell->insertParticle(object);
        griddle.push_front(funcell);
    }
    else
    {

        for(CellIterator cat = griddle.begin(); cat!=griddle.end(); ++cat)
        {
            val=(*cat)->insertParticle(object);
            if(val==0)
            {
            return;
            }

        }
        if(val==2)
        {
        funcell->define_cell(object->pos.x-0.5f, object->pos.y-0.5f, object->pos.x+25.5f, object->pos.y+25.5f);
        funcell->insertParticle(object);
        griddle.push_front(funcell);
        }
        return;
    }


}

void grid::range_cells()
{
    ParticleIterator cheese;
    for(CellIterator it=griddle.begin() ; it!=griddle.end() ; it++)
    {
        fire.merge((*it)->pop_list());
        fire.unique();
    for(cheese=fire.begin(); cheese!=fire.end() ; cheese++)
    {
        insert_cell((*cheese));
        cheese=fire.erase(cheese);
    }

    }
    for(CellIterator mom=griddle.begin() ; mom!=griddle.end() ; mom++)
    {
        if((*mom)->is_empty())
            mom=griddle.erase(mom);
    }
}

int grid::size()
{
    return griddle.size();
}



