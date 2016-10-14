#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <iostream>
#include <conio.h>
/* Utility library
void Pause()
int GetInt(int Lo, int Hi)*/
using namespace std;

//--------------------------------------------------
void Pause()
{
    /* Displays a message for user to enter a key.*/
    cout << "Press any key to continue." << endl;
    getch(); // Pause for user to hit a key.
}
//--------------------------------------------------
int GetInt(int Lo, int Hi)
/* Obtains and returns a value between Lo and Hi.*/
{
    int Entry;
    cin >> Entry;
    while (Entry < Lo || Entry > Hi)
    {
        cout << "Value must be between " << Lo << " and " << Hi << endl;
        cout << "Please re-enter: ";
        cin >> Entry;
    }
    return (Entry);
}
//------------------------------------------------------------------

void sortlist(vector<int>data, int lenolist)
{
    vector<int> refer = data
    vector<int> sorted;
    sorted.resize(lenolist);
    bool cont = true;
    while (cont)
    {
        if (lenolist <= 0)
        {
            cout << "That is not a valid number." << endl;
            break;
        }
        else if (lenolist == 1)
        {
            sorted[0] = refer[0];
            break;
        }
        else
        {
            for (int x = 0; x < lenolist-1; x++)
            {
                if (sorted[x] > sorted[x+1])
                {
                    sorted[x] = refer[x+1];
                    sorted[x+1] = refer[x];
                    refer[x] = sorted [x];
                    refer[x+1] = sorted [x+1];// the original list is readjusted for accuracy and to avoid repetition
                }
                else
                {
                    sorted[x] = refer[x];
                    sorted[x+1] = refer[x+1];
                }
            }
            for (int z = 0; z<lenolist-1; z++)
            {
                if (sorted[z] <= sorted[z+1])
                {
                    cont = false;
                }
                else if (sorted[z] > sorted[z+1])
                {
                    cont = true;
                    break;
                }
            }
        }
    }
    for (int q = 0; q < lenolist; q++)
    {
        cout << sorted[q] << ", ";
    }
    cout << endl;
}
//----------------------------------------------------------------

void Signature()
{
    cout << "This library was written by Tiger Kong";
}

#endif // UTILITY_H_INCLUDED
