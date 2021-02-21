#include <iostream>

#include "Battleship.h"

void runGame(Battleship&);
void printGameOverScreen(Battleship&);

int main() {

    Battleship battleship;

    bool done = false;
    int menu = 0;

    std::string playerName;
    std::string opponentName;

    while (!done) {

        system("clear");

        std::cout << std::endl << std::endl << std::endl << std::endl;
        std::cout << "\t*------------------------------*" << std::endl;
        std::cout << "\tBattleship Game" << std::endl;
        std::cout << "\t*------------------------------*" << std::endl << std::endl;

        std::cout << "\tLast Winner: " << battleship.getWinner().getName() << std::endl;
        std::cout << "\tPlayer Created: ";
        if (!battleship.isPlayerCreated()) { std::cout << "NO"; }
        else { std::cout << "YES"; }
        std::cout << std::endl;

        std::cout << "\tOpponent Created: ";
        if (!battleship.isOpponentCreated()) { std::cout << "NO"; }
        else { std::cout << "YES"; }
        std::cout << std::endl << std::endl;

        std::cout << "\t1. Start Game" << std::endl << std::endl;
        std::cout << "\t2. Create your player and place ships" << std::endl;
        std::cout << "\t3. Generate opponent and their ships" << std::endl;
        std::cout << "\t4. Display player and opponent ships (Debug)" << std::endl << std::endl;
        std::cout << "\tOther: Exit game" << std::endl << std::endl << "\t";
        std::cin >> menu;

        switch (menu) {

        case 1:

            battleship.startGame();

            if (battleship.isGameReady()) {

                runGame(battleship);

                if (battleship.isGameOver()) { 
                    
                    printGameOverScreen(battleship); 
                }
            }

            break;

        case 2:

            battleship.generatePlayer();
            playerName = battleship.getPlayer().getName();
            
            break;
        
        case 3:

            battleship.generateOpponent();
            opponentName = battleship.getOpponent().getName();

            break;

        case 4:

            system("clear");

            std::cout << std::endl << std::endl << std::endl;
            battleship.printGrid(playerName, battleship.getPlayerShipsGrid());
            std::cout << std::endl;
            battleship.printGrid(opponentName, battleship.getOpponentShipsGrid());
            std::cout << std::endl << std::endl << "\tPress ENTER to go back to menu" << std::endl;

            std::cin.ignore().get();

            break;

        default:

            done = true;

            system("clear");

            break;
        }
    }

    return 0;
}

void runGame(Battleship &battleship) {

    while (!battleship.isGameOver()) {

        if (battleship.isPlayersTurn()) {

            bool validStrike = false;
            bool invalidStrikeString = false;

            while (!validStrike) {

                std::string strikeString = "";

                system("clear");

                std::cout << std::endl << std::endl << std::endl << std::endl;
                battleship.printGrid("Your Turn", battleship.getPlayerStrikesGrid());

                if (invalidStrikeString) {

                    std::cout << std::endl << "\tInvalid position, try again!";
                }

                std::cout << std::endl << "\tPlease enter the position of your strike (or Q to quit) and press ENTER: ";
                std::cin >> strikeString;
                std::cout << std::endl;

                if (strikeString == "q" || strikeString == "Q") { return; }
                else {

                    if (convertStringToPosition(strikeString).getNumber() != 0) {

                        battleship.playPlayerStrike(convertStringToPosition(strikeString));

                        validStrike = true;
                        invalidStrikeString = false;
                    }
                    else { invalidStrikeString = true; }
                }
            }

            std::string input = "";

            system("clear");

            std::cout << std::endl << std::endl << std::endl << std::endl;
            battleship.printGrid("Your Turn", battleship.getPlayerStrikesGrid());

            if (battleship.getLastPlayerStrike() == 'H') {

                std::cout << std::endl << "\tYou hit one of " << battleship.getOpponent().getName() << "'s ships!" << std::endl;
            } 
            else if (battleship.getLastPlayerStrike() == 'M') {

                std::cout << std::endl << "\tYou missed!" << std::endl;
            }
            else {

                std::cout << std::endl << "\tERROR: Failed to get last strike from player." << std::endl;
            }

            std::cout << std::endl << "\tPress ENTER to pass turn to opponent ";

            std::cin.ignore().get();
        }
        else if (battleship.isOpponentsTurn()) {

            system("clear");

            std::cout << std::endl << std::endl << std::endl << std::endl;
            battleship.printGrid("Opponent\'s Turn", battleship.getPlayerShipsGrid());

            std::chrono::seconds duration(1);
            std::this_thread::sleep_for(duration);

            system("clear");

            battleship.playOpponentStrike();

            std::cout << std::endl << std::endl << std::endl << std::endl;
            battleship.printGrid("Opponent\'s Turn", battleship.getPlayerShipsGrid());

            if (battleship.getLastOpponentStrike() == 'H') {

                std::cout << std::endl << "\t" << battleship.getOpponent().getName() << " hit one of your ships!" << std::endl;
            } 
            else if (battleship.getLastOpponentStrike() == 'M') {

                std::cout << std::endl << "\t" << battleship.getOpponent().getName() << " missed!" << std::endl;
            }
            else {

                std::cout << std::endl << "\tERROR: Failed to get last strike from opponent." << std::endl;
            }

            std::cout << std::endl << "\tPress ENTER to take your turn ";

            std::cin.ignore().get();
        }
    }
}

void printGameOverScreen(Battleship& battleship) {

    system("clear");

    std::cout << std::endl << std::endl << std::endl << std::endl;
    
    if (battleship.getWinner().getName() == battleship.getPlayer().getName()) {

        std::cout << "\tYou win! Congratulations!" << std::endl << std::endl;
    }
    else {
        
        std::cout << std::endl << "\tYou lose! Better luck next time!";
    }

    std::cout << std::endl << "\tPress ENTER to return to main menu ";

    std::cin.ignore().get();
}