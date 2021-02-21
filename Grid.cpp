#include "Grid.h"

////////////////////////////////////////////////////////////
//      Constructor
////////////////////////////////////////////////////////////

Grid::Grid() {

    x = 10;
    y = 10;

    gridContents = new char*[x]();

    for (int i = 0; i < x; i++) {

        gridContents[i] = new char[y]();
    }
}

////////////////////////////////////////////////////////////
//      Getters
////////////////////////////////////////////////////////////

char** Grid::getContents() { return gridContents; }

char Grid::getCharacterAtPosition(Position position) {

    if (position.getNumber() == 0) {

        return '_';
    }
    else {

        return gridContents[position.getNumber() - 1][convertLetterToNumber(position.getLetter()) - 1];
    }
}

////////////////////////////////////////////////////////////
//      Add Ship
////////////////////////////////////////////////////////////

void Grid::addShip(Ship ship) {

    int coordinateCount = 0;
    std::vector<int> xCoordinates;
    std::vector<int> yCoordinates;

    int currentX, currentY;

    std::string shipType = ship.getShipType();
    int shipLength = ship.getShipLength();
    Position position = ship.getPosition();
    std::string orientation = ship.getOrientation();

    char coordinateSymbol;

    if (shipType == "Carrier") { coordinateSymbol = 'A'; }
    else if (shipType == "Battleship") { coordinateSymbol = 'B'; }
    else if (shipType == "Cruiser") { coordinateSymbol = 'C'; }
    else if (shipType == "Submarine") { coordinateSymbol = 'S'; }
    else if (shipType == "Destroyer") { coordinateSymbol = 'D'; }

    if (orientation == "H") {

        for (int i = 0; i < shipLength; i++) {

            coordinateCount++;
            xCoordinates.push_back(convertLetterToNumber(position.getLetter()) + i - 1);
            yCoordinates.push_back(position.getNumber() - 1);
        }
    }
    else if (orientation == "V") {

        for (int i = 0; i < shipLength; i++) {

            coordinateCount++;
            xCoordinates.push_back(convertLetterToNumber(position.getLetter()) - 1);
            yCoordinates.push_back(position.getNumber() + i - 1);
        }
    }

    for (int i = 0; i < coordinateCount; i++) {

        gridContents[yCoordinates[i]][xCoordinates[i]] = coordinateSymbol;
    }
}

////////////////////////////////////////////////////////////
//      Add Strike
////////////////////////////////////////////////////////////

void Grid::addStrike(Position position) {

    if (gridContents[position.getNumber() - 1][convertLetterToNumber(position.getLetter()) - 1] == '~') {

        gridContents[position.getNumber() - 1][convertLetterToNumber(position.getLetter()) - 1] = 'M';
    }
    else {

        gridContents[position.getNumber() - 1][convertLetterToNumber(position.getLetter()) - 1] = 'H';
    }
}

////////////////////////////////////////////////////////////
//      Add Strike with Character
////////////////////////////////////////////////////////////

void Grid::addStrike(Position position, char character) {

    gridContents[position.getNumber() - 1][convertLetterToNumber(position.getLetter()) - 1] = character;
}

////////////////////////////////////////////////////////////
//      Check Strike
////////////////////////////////////////////////////////////

bool Grid::checkStrike(Position position) {

    if (
        
        gridContents[position.getNumber() - 1][convertLetterToNumber(position.getLetter()) - 1] == 'H' ||
        gridContents[position.getNumber() - 1][convertLetterToNumber(position.getLetter()) - 1] == 'M'
    ) {

        return false;
    }
    else {

        return true;
    }
}

////////////////////////////////////////////////////////////
//      Initialize Grid Contents
////////////////////////////////////////////////////////////

void Grid::initializeGridContents() {

    for (int i = 0; i < x; i++) {

        for (int j = 0; j < y; j++) {

            gridContents[i][j] = '~';
        }
    }
}

////////////////////////////////////////////////////////////
//      Print Contents
////////////////////////////////////////////////////////////

void Grid::printContents() {

    for (int i = 0; i < x; i++) {

        if (i < 9) { std::cout << "\t" << i + 1 << "  "; }
        else { std::cout << "\t" << i + 1 << " "; }

        for (int j = 0; j < y; j++) {

            std::cout << gridContents[i][j] << " ";
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}