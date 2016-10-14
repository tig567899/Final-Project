#include "race.h"

race::race(int cars)
{
    quota = new vector <car*> ();
}

void race::add_car(car* Car)
{
    quota->push_back(Car);
}

int race::return_win()
{
    return win;
}

/**
 * Determines whether or not the player has won
 */
void race::playerwin()
{
    if (win <=0 || win > quota->size())
    {
        win = 0;
    }
}

/**
 * Checks for CPU victories
 */
void race::checkwin()
{
    for(int x = 0; x < quota->size(); x++)
    {
        if (quota->at(x)->return_laps() == 3)
        {
            win = x+1;
            break;
        }
    }
}

vector<car*>* race::return_quota()
{
    return quota;
}
