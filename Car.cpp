#include "Car.h"
#include "cardata.h"

car::car(int difficult, int position)
{
    x = -80.0 - position*2;
    z = 0.0;
    lx = 0.0;
    lz = -1;
    angle = 0.0;
    difficulty = difficult;
    completed_turn = false;
    laps = 0;
    distance = 0;
    complete = true;
}
/**
 * Main AI, controlling decision making and deciding when to turn
 */
void car::ai()
{
    if (abs(x) >= 79.5 && abs(z) >=79.5)
    {
        turn();
    }
    else
    {
        move_forward();
    }
    if((x > -lx*5 || x < 5*lx) && z < 0 && !complete)
    {
        complete = true;
        laps ++; // update laps
    }
    else if (z>1 && x >0)
    {
        complete = false;
    }
}
/**
 * Moving cars forward
 */
void car::move_forward()
{
    x += lx*difficulty/200;
    z += lz*difficulty/200;
    distance += difficulty/10;
    completed_turn = false;
}

/**
 * Turning Function
 */
void car::turn()
{
    if (!completed_turn)
    {
        origangle = angle;
        completed_turn = true;
    }
    if (origangle + 1.565 > angle)
    {
        angle += 0.005+ 0.001* difficulty;
        lx = sin (angle);
        lz = -cos(angle);
        x += lx*difficulty/500;
        z += lz*difficulty/500;
    }
    else
    {
        x += lx*difficulty/200;
        z += lz*difficulty/200;
    }
}

float car::return_angle()
{
    return angle;
}
float car::return_x()
{
    return x;
}
float car::return_z()
{
    return z;
}
int car::return_speed()
{
    return difficulty;
}
float car::return_distance()
{
    return distance;
}
int car::return_laps()
{
    return laps;
}
