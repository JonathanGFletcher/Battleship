#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>

#include "Exceptions.h"
#include "HelperFunctions.h"

#include "Player.h"
#include "Ship.h"
#include "Grid.h"
#include "Position.h"

class Battleship {

private:

    Player player, opponent;
    Grid playerShips, opponentShips, playerStrikes, opponentStrikes;

    bool playerCreated;
    bool opponentCreated;
    bool gameReady;
    bool playersTurn;
    bool opponentsTurn;
    Position lastPlayerStrike;
    Position lastOpponentStrike;
    bool winner;
    bool loser;
    bool gameOver;

    bool verifyShipPlacement(Ship, Grid);
    bool checkWin();

public:

    Battleship();

    void startGame();

    void generatePlayer();
    void generateOpponent();

    void playPlayerStrike(Position);
    void playOpponentStrike();

    void printGrid(const std::string, Grid);

    bool isPlayerCreated() { return playerCreated; }
    bool isOpponentCreated() { return opponentCreated; }
    bool isGameReady() { return gameReady; }
    Player getPlayer() { return player; }
    Player getOpponent() { return opponent; }
    Grid getPlayerShipsGrid() { return playerShips; }
    Grid getPlayerStrikesGrid() { return playerStrikes; }
    Grid getOpponentShipsGrid() { return opponentShips; }
    Grid getOpponentStrikesGrid() { return opponentStrikes; }
    bool isPlayersTurn() { return playersTurn; }
    bool isOpponentsTurn() { return opponentsTurn; }
    char getLastPlayerStrike() { return this->getPlayerStrikesGrid().getCharacterAtPosition(lastPlayerStrike); }
    char getLastOpponentStrike() { return this->getOpponentStrikesGrid().getCharacterAtPosition(lastOpponentStrike); }
    bool isGameOver() { return gameOver; }
    Player getWinner() { 
        
        if (winner) { return player; } 
        else if (loser) { return opponent; } 
        else { Player empty; return empty; } 
    }
};

#endif