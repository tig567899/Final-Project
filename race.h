#ifndef RACE_H_INCLUDED
#define RACE_H_INCLUDED

#include "Car.h"
#include <vector>

class race
{
    public:
        race(int);
        void add_car(car*);
        void playerwin();
        void checkwin();
        void scan();
        void get_distance();
        vector<car*>* return_quota();
        int return_win();
    private:
        vector<car*>* quota;
        int win;
};

#endif // RACE_H_INCLUDED
