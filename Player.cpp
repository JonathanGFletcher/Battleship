#include "Player.h"

////////////////////////////////////////////////////////////
//      Constructor
////////////////////////////////////////////////////////////

Player::Player() {

    name = "";
}

////////////////////////////////////////////////////////////
//      Constructor with Parameters
////////////////////////////////////////////////////////////

Player::Player(std::string& name, std::vector<Ship>& ships) {

    this->name = name;
    this->ships = ships;
}

////////////////////////////////////////////////////////////
//      Getters
////////////////////////////////////////////////////////////

const std::string Player::getName() { return name; }
const std::vector<Ship>& Player::getShips() { return ships; }

////////////////////////////////////////////////////////////
//      Setters
////////////////////////////////////////////////////////////

void Player::setName(const std::string& name) {

    this->name = name;
}

////////////////////////////////////////////////////////////
//      Add Ship
////////////////////////////////////////////////////////////

void Player::addShip(const Ship ship) {

    this->ships.push_back(ship);
}