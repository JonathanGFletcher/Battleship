#include "Ship.h"

////////////////////////////////////////////////////////////
//      Constructor
////////////////////////////////////////////////////////////

Ship::Ship(std::string shipType, Position position, std::string orientation) {

    this->shipType = shipType;

    if (this->shipType == "Carrier")
        shipLength = 5;
    else if (this->shipType == "Battleship")
        shipLength = 4;
    else if (this->shipType == "Cruiser" || this->shipType == "Submarine")
        shipLength = 3;
    else if (this->shipType == "Destroyer")
        shipLength = 2;

    this->position = position;
    this->orientation = orientation;
}

////////////////////////////////////////////////////////////
//      Getters
////////////////////////////////////////////////////////////

const std::string& Ship::getShipType() { return shipType; }
const int& Ship::getShipLength() { return shipLength; }
const Position& Ship::getPosition() {return position; }
const std::string& Ship::getOrientation() { return orientation; }

////////////////////////////////////////////////////////////
//      Setters
////////////////////////////////////////////////////////////

void Ship::setShipType(const std::string& shipType) {

    this->shipType = shipType;
}

void Ship::setShipLength(const int& shipLength) {

    this->shipLength = shipLength;
}

void Ship::setPosition(Position position) {

    this->position = position;
}

void Ship::setOrientation(const std::string& orientation) {

    this->orientation = orientation;
}

////////////////////////////////////////////////////////////
//      Get Ship Description
////////////////////////////////////////////////////////////

std::string Ship::getShipDescription() {

    std::string description = "";

    description += this->shipType;
    description += " ";
    description += position.getLetter();
    description += position.getNumber();
    description += " ";
    description += orientation;
    
    return description;
}