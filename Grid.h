#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <math.h>

#include "HelperFunctions.h"

#include "Ship.h"

using namespace std;

class Grid {

private:

    int x, y;
    char** gridContents;

public:

    Grid();

    char** getContents();
    char getCharacterAtPosition(Position);
    void addShip(Ship);
    void addStrike(Position);
    void addStrike(Position, char);
    bool checkStrike(Position);
    void initializeGridContents();
    void printContents();
};

#endif