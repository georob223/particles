#include "particle.h"
#include <sstream>


ParticleSystem::ParticleSystem( int width, int height )
{
    int x=200;
    int y=200;
    int n=0;
    m_transparent = sf::Color( 0, 0, 0, 0 );
    m_image.create( width, height,sf::Color::Transparent );
    //m_image.createMaskFromColor(m_transparent,0);
    m_texture.create( width, height);
    for(y=250;y<270;y++)
        for(x=250;x<375;x++)
        {
    m_position[n].x	= x;
    m_position[n].y	= y;
    n++;
        }
    m_particleSpeed	= 60.0f;
    m_dissolve	= false;
    m_dissolutionRate = 4;
    m_shape		= Shape::CIRCLE;
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::fuel( unsigned int particles )
{
    int r=0,b=0,g=0;
    static int n=0;
    Particle* particle;
    float speedmux = 100.0f;


    if(m_particles.size()<100000)
    {
    for( unsigned int i = 0; i < particles; i++ )
    {
        particle = new Particle();
        if(particle==NULL)
            return;
    if(n>2500)
        n=0;

        particle->pos.x = m_position[n].x;
        particle->pos.y = m_position[n].y;
        n++;

        switch( m_shape )
        {
        case Shape::CIRCLE:
            //angle = (float(rand()%7)+float(((rand()%1000)+1)/1000.0f));
            switch(rand()%4)
            {
            case 0:
                particle->vel.x = ((float(rand()%10000)+1)/speedmux);
                particle->vel.y = ((float(rand()%10000)+1)/speedmux);
                break;
            case 1:
                particle->vel.x = -((float(rand()%10000)+1)/speedmux);
                particle->vel.y = -((float(rand()%10000)+1)/speedmux);
                break;
            case 2:
                particle->vel.x = ((float(rand()%10000)+1)/speedmux);
                particle->vel.y = -((float(rand()%10000)+1)/speedmux);
                break;
            case 3:
                particle->vel.x = -((float(rand()%10000)+1)/speedmux);
                particle->vel.y = ((float(rand()%10000)+1)/speedmux);
                break;
            default:
                particle->vel.x = -((float(rand()%10000)+1)/speedmux);
                particle->vel.y = ((float(rand()%10000)+1)/speedmux);

            }
            break;
        case Shape::SQUARE:
            particle->vel.x = 2.0f;//float((rand()%1000)+1);
            particle->vel.y = 1.0f;//float((rand()%1000)+1);
            break;
        default:
            particle->vel.x = 0.5f; // Easily detected
            particle->vel.y = 0.5f; // Easily detected
        }

        if( particle->vel.x == 0.0f && particle->vel.y == 0.0f)
        {
            delete particle;
            //continue;
        }
        else
        {
            if(r==255||b==255||g==255)
            {
                r=0;
                b=100;
                g=0;
            }
            particle->color.r = r++;//rand()%255;
            particle->color.g = b+=2;//rand()%255;
            particle->color.b = g+=3;//rand()%255;
            particle->color.a = 255;
            //m_particles.push_back( particle );
            noms.insert_cell(particle);
            //noms.status();
        }
    }

    }
   /* else
    {
        delrandparts(10);
    }*/
}
/*
pull cell
    check for collision
    update velocities --grav, wells, collisions
    update xy
    delete outliers -- exceeds screen, other updates
    update cells -- move particles into queue for reallocation

push cell onto render list

*/
void ParticleSystem::delrandparts(int number)
{

    int deathnumber;
    int totalsteps=m_particles.size();
    int deathsteps=0;

    ParticleIterator execute=m_particles.begin();
    while(number>=0)
    {
        deathnumber=rand()%3;
            (*execute)->color.a=0;
            if(deathnumber==0)
            {
            execute++;
            }
            else if(deathnumber==1)
            {
                execute++;
                execute++;
            }
            else if(deathnumber==2)
            {
                execute++;
                execute++;
                execute++;
            }
            deathsteps+=(deathnumber+1);
            if(totalsteps<deathsteps)
            {
                execute=m_particles.begin();
            }
            number--;

    }
}

void ParticleSystem::update()
{
    std::cout<<"Pre: "<<noms.size()<<std::endl;
    noms.range_cells();
    std::cout<<"Post: "<<noms.size()<<std::endl;
    sf::Time convert;
    convert = m_clock.getElapsedTime();
    float time = convert.asSeconds();
    m_clock.restart();
    sf::Vector2u cat;
    cat=m_image.getSize();

    for( CellIterator it = noms.begin(); it != noms.end(); it++ )
    {
        for( ParticleIterator its = (*it)->begin();its != (*it)->end(); its++ )
        {

        (*its)->vel.x += m_gravity.x * time;
        (*its)->vel.y += m_gravity.y * time;

        (*its)->pos.x += (*its)->vel.x * time; //* m_particleSpeed;
        (*its)->pos.y += (*its)->vel.y * time; //* m_particleSpeed;
       //if( m_dissolve ) (*it)->color.a -= m_dissolutionRate;

        if( (*its)->pos.x > float(cat.x) || (*its)->pos.x < 0.0f || (*its)->pos.y > float(cat.y) || (*its)->pos.y < 0.0f || (*its)->color.a < 10 )
        {
            if((*its)->color.a < 10)
                m_image.setPixel( (int)(*its)->pos.x, (int)(*its)->pos.y, m_transparent );
            its = (*it)->erase( its );
        }
        }

    }
    particle_hit_loop();

}

sf::Vector2f ParticleSystem::grav_well(sf::Vector2f well, sf::Vector2f partpos, float strength)
{
    sf::Vector2f change, distance;
    float distant=0.0f;
    change.x=0.0f;
    change.y=0.0f;
    distance.x=(partpos.x-well.x);
    distance.y=(partpos.y-well.y);
    distance.x*=distance.x;
    distance.y*=distance.y;

    if(!(distance.x+distance.y<=strength*strength*10))
    {
        return change;
    }
    distant=38000/(distance.x+distance.y);
    strength=(strength/distant);

    if((well.x<partpos.x)&&(well.y<partpos.y))
    {
        change.x=-strength;
        change.y=-strength;
        return change;
    }

    if((well.x<partpos.x)&&(well.y>partpos.y))
    {
        change.x=-strength;
        change.y=strength;
        return change;
    }
    if((well.x<partpos.x)&&(well.y==partpos.y))
    {
        change.x=-strength;
        change.y=0.0;
        return change;
    }
    if((well.x>partpos.x)&&(well.y==partpos.y))
    {
        change.x=strength;
        change.y=0.0;
        return change;
    }
    if((well.x>partpos.x)&&(well.y>partpos.y))
    {
        change.x=strength;
        change.y=strength;
        return change;
    }
    if((well.x>partpos.x)&&(well.y<partpos.y))
    {
        change.x=strength;
        change.y=-strength;
        return change;
    }
    if((well.x==partpos.x)&&(well.y<partpos.y))
    {
        change.x=0.0;
        change.y=-strength;
        return change;
    }
    if((well.x==partpos.x)&&(well.y>partpos.y))
    {
        change.x=0.0;
        change.y=strength;
        return change;
    }

    return change;
}



void ParticleSystem::update(sf::Vector2f * local_well, float * pull, int wells)
{

    sf::Time convert;
    sf::Vector2f local_change;
    local_change.x=0.0;
    local_change.y=0.0;
    convert = m_clock.getElapsedTime();
    float time = convert.asSeconds();
    m_clock.restart();
    sf::Vector2u cat;
    cat=m_image.getSize();

    for( ParticleIterator it = m_particles.begin(); it != m_particles.end(); it++ )
    {
        for(int i=0; i<wells; i++)
            local_change+=grav_well(local_well[i],(*it)->pos,pull[i]);

        (*it)->vel.x += (m_gravity.x+local_change.x) * time;
        (*it)->vel.y += (m_gravity.y+local_change.y) * time;

        local_change.x=0.0f;
        local_change.y=0.0f;

        (*it)->pos.x += (*it)->vel.x * time * m_particleSpeed;
        (*it)->pos.y += (*it)->vel.y * time * m_particleSpeed;

        if( m_dissolve ) (*it)->color.a -= m_dissolutionRate;



        if( (*it)->pos.x > float(cat.x) || (*it)->pos.x < 0.0f || (*it)->pos.y > float(cat.y) || (*it)->pos.y < 0.0f || (*it)->color.a < 10 )
        {
            /*if((*it)->color.a < 10)
                m_image.setPixel( (int)(*it)->pos.x, (int)(*it)->pos.y, m_transparent );*/
            it = m_particles.erase( it );
            if( it == m_particles.end() ) return;
        }

    }

    particle_hit_loop();

}

void ParticleSystem::render()
{

    sf::Vector2u imsize=m_image.getSize();

    for(CellIterator its = noms.begin(); its!=noms.end();its++)
    for( ParticleIterator it = (*its)->begin(); it != (*its)->end(); it++ )
    {
        if((unsigned int)(*it)->pos.x<imsize.x&&(unsigned int)(*it)->pos.y<imsize.y)
            m_image.setPixel( (int)(*it)->pos.x, (int)(*it)->pos.y, (*it)->color );
    }

    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);


}

void ParticleSystem::remove()
{
    /*if(m_particles.empty())
        return; */

    sf::Vector2u imsize=m_image.getSize();

    for(CellIterator its = noms.begin(); its!=noms.end();its++)
    {
    for( ParticleIterator it = (*its)->begin(); it != (*its)->end(); it++ )
    {
        if((unsigned int)(*it)->pos.x<imsize.x&&(unsigned int)(*it)->pos.y<imsize.y)
            m_image.setPixel( (int)(*it)->pos.x, (int)(*it)->pos.y, m_transparent );
    }
        its=noms.is_empty(its);
    }

}

void ParticleSystem::particle_hit_loop()
{
    ParticleIterator Pointer1;
    ParticleIterator Pointer2;


        for( CellIterator its = noms.begin() ; its!=noms.end() ; its++)
        {
            ParticleIterator it2 = (*its)->begin();
            Pointer2=it2;
        for( ; it2 != (*its)->end() ; it2++ )
        {
            Pointer1=it2;

        if(pixel_collision((*Pointer1)->pos.x,(*Pointer1)->pos.y,(*Pointer2)->pos.x,(*Pointer2)->pos.y)&&((*Pointer1)!=(*Pointer2)))
        {
            change_position(Pointer1, Pointer2);
        }
        }
        }
}

bool ParticleSystem::pixel_collision(int x, int y, int x1, int y1)
{
    if(x==x1&&y==y1)
    {
        return true;
    }
    else
        return false;

}

void ParticleSystem::change_position(ParticleIterator first, ParticleIterator second)
{
    float averagex;
    float averagey;

    averagex = ((*first)->vel.x+(*second)->vel.x)/2;
    averagey = ((*first)->vel.y+(*second)->vel.y)/2;

    (*first)->vel.x+=averagex;
    (*second)->vel.x-=averagex;
    (*first)->vel.y-=averagey;
    (*second)->vel.y+=averagey;
}

