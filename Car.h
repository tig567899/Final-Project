#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

class car
{
    public:
        car(int, int);
        void ai();
        void move_forward();
        void move_back();
        void turn();
        void pass();
        float return_angle();
        int return_speed();
        float return_x();
        float return_z();
        float return_lx();
        float return_lz();
        float return_distance();
        int return_laps();
        void adjust_rank(int);
        void adjust_info(bool, float);
    private:
        float x, z;
        float lx, lz;
        float angle, origangle;
        int laps;
        int difficulty;
        bool completed_turn;
        float distance;
        bool complete;
};

#endif // CAR_H_INCLUDED
