#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Ship.h"

class Player {

private:

    std::string name;
    std::vector<Ship> ships;

public:

    Player();
    Player(std::string&, std::vector<Ship>&);

    const std::string getName();
    const std::vector<Ship>& getShips();

    void setName(const std::string&);
    void addShip(const Ship);
};

#endif