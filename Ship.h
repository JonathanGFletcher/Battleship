#ifndef SHIP_H
#define SHIP_H

#include <string>

#include "Position.h"

class Ship {

private:

    std::string shipType;
    int shipLength;
    Position position;
    std::string orientation;

public:

    Ship(std::string shipType, Position position, std::string orientation);

    const std::string& getShipType();
    const int& getShipLength();
    const Position& getPosition();
    const std::string& getOrientation();

    void setShipType(const std::string&);
    void setShipLength(const int&);
    void setPosition(Position);
    void setOrientation(const std::string&);

    std::string getShipDescription();
};

#endif