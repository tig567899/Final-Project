#ifndef CARDATA_H_INCLUDED
#define CARDATA_H_INCLUDED

class car;

struct cardata
{
    car* target;
    int placement;
    bool pass;
    float separation;
};

#endif // CARDATA_H_INCLUDED
