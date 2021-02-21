#include "Battleship.h"

////////////////////////////////////////////////////////////
//      Constructor
////////////////////////////////////////////////////////////

Battleship::Battleship() {

    playerShips.initializeGridContents();
    playerStrikes.initializeGridContents();
    opponentShips.initializeGridContents();
    opponentStrikes.initializeGridContents();

    gameReady = false;
    playerCreated = false;
    opponentCreated = false;
    winner = false;
    loser = false;
    gameOver = true;
}

////////////////////////////////////////////////////////////
//      Start Game
////////////////////////////////////////////////////////////

void Battleship::startGame() {

    try {

        if ((!playerCreated) || (!opponentCreated)) { throw FailedToStartGame(); }
        else {

            gameReady = true;
            playersTurn = true;
            opponentsTurn = false;
            winner = false;
            loser = false;
            gameOver = false;
        }
    }
    catch (FailedToStartGame exception) {

        std::cout << "\t" << exception.what() << std::endl;

        std::chrono::seconds duration(1);
        std::this_thread::sleep_for(duration);
    }
}

////////////////////////////////////////////////////////////
//      Generate Player
////////////////////////////////////////////////////////////

void Battleship::generatePlayer() {

    Player newPlayer;
    this->player = newPlayer;
    Grid newGrid;
    newGrid.initializeGridContents();
    this->playerShips = newGrid;

    Player player;
    std::string name = "";
    std::string currentShipType[5] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
    int shipCounter = 0;
    char currentOrientation;
    bool validOrientation;
    bool invalidOrientationMessage = false;
    std::string currentPosition = "";
    bool validPosition;
    bool invalidPositionMessage = false;

    std::string shipOrientation;

    system("clear");
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
    std::cout << "\t\tPlease enter player name: ";
    std::cin >> name;

    if (name != "") {

        player.setName(name);
    }
    else {

        player.setName("Player");
    }

    while (shipCounter < 5) {

        validOrientation = false;
        validPosition = false;

        while (!validOrientation) {

            system("clear");

            std::string gridTitle = "";
            gridTitle += name;
            gridTitle += "\'s Ships";

            std::cout << std::endl << std::endl << std::endl << std::endl;
            printGrid(gridTitle, playerShips);

            if (invalidOrientationMessage) {

                std::cout << "\tInvalid Orientation!" << std::endl;
                std::cout << std::endl << std::endl << std::endl << std::endl;
            }
            else {

                std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            }

            std::cout << "\tPlease enter the orientation of your " << currentShipType[shipCounter] << std::endl;
            std::cout << "\t(Either H (horizontal) or V (vertical))" << std::endl << std::endl << std::endl << "\t";
            std::cin >> currentOrientation;
            std::cout << std::endl;

            try {

                currentOrientation = toupper(currentOrientation);

                if (currentOrientation == 'H') {

                    shipOrientation = "H";

                    invalidOrientationMessage = false;
                    validOrientation = true;
                }
                else if (currentOrientation == 'V') {

                    shipOrientation = "V";

                    invalidOrientationMessage = false;
                    validOrientation = true;
                }
                else { throw InvalidShipOrientation(); }
            }
            catch (InvalidShipOrientation exception) {

                invalidOrientationMessage = true;
            }
        }

        while (!validPosition) {

            system("clear");

            std::string gridTitle = "";
            gridTitle += name;
            gridTitle += "\'s Ships";

            std::cout << std::endl << std::endl << std::endl << std::endl;
            printGrid(gridTitle, playerShips);

            if (invalidPositionMessage) {

                std::cout << "\tInvalid Position!" << std::endl;
                std::cout << std::endl << std::endl << std::endl << std::endl;
            }
            else {

                std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            }

            std::cout << "\tPlease enter the position of your " << currentShipType[shipCounter] << std::endl;
            std::cout << "\t(Examples of position would be A6 or F3)" << std::endl << std::endl << std::endl << "\t";
            std::cin >> currentPosition;
            std::cout << std::endl;

            try {

                if (convertStringToPosition(currentPosition).getNumber() == 0) {

                    throw InvalidPosition();
                }
                else {

                    Ship currentShip(currentShipType[shipCounter], convertStringToPosition(currentPosition), shipOrientation);

                    if (!verifyShipPlacement(currentShip, playerShips)) {

                        throw InvalidShipPlacement();
                    }
                    else {

                        invalidPositionMessage = false;
                        validPosition = true;

                        shipCounter++;
                        player.addShip(currentShip);
                        playerShips.addShip(currentShip);

                        playerCreated = true;
                    }
                }
            }
            catch (InvalidPosition exception) {

                std::cout << exception.what() << std::endl;
                invalidPositionMessage = true;
            }
            catch (InvalidShipPlacement exception) {

                std::cout << exception.what() << std::endl;
                invalidPositionMessage = true;
            }
        }
    }

    this->player = player;
}

////////////////////////////////////////////////////////////
//      Generate Opponent
////////////////////////////////////////////////////////////

void Battleship::generateOpponent() {

    Player newOpponent;
    this->opponent = newOpponent;
    Grid newGrid;
    newGrid.initializeGridContents();
    this->opponentShips = newGrid;

    std::ifstream nameFile;
    std::ifstream shipFile;

    int shipPlacementSelection = (rand() % 8) + 1;
    std::string shipPlacementFileName = "";
    shipPlacementFileName += "ship_placement";
    shipPlacementFileName += std::to_string(shipPlacementSelection);
    shipPlacementFileName += "_good.csv";

    nameFile.open("names.txt");
    shipFile.open(shipPlacementFileName);

    try {

        if (!nameFile.is_open()) {

            throw FailedToOpenFile();
        }
        else {

            std::string fileContents = "";
            std::string fileElement = "";
            std::string name = "";
            std::vector<std::string> names;
            
            while (std::getline(nameFile, fileElement)) {

                fileContents += fileElement;
                fileContents += ",";
            }

            char contents[fileContents.size() + 1];
            std::strcpy(contents, fileContents.c_str());
            char* element = std::strtok(contents, " ,");

            while (element != NULL) {

                names.push_back(element);

                element = std::strtok(NULL, " ,");
            }

            int sizeOfNames = names.size();
            int randomIndex = rand() % sizeOfNames;

            opponent.setName(names[randomIndex]);
        }

        if (!shipFile.is_open()) {

            throw FailedToOpenFile();
        }
        else {

            std::vector<std::string> fileContents;
            std::string fileElement = "";
            int shipCounter = -1;

            while (std::getline(shipFile, fileElement)) {

                fileContents.push_back(fileElement);
            }

            for (std::string& ship: fileContents) {

                std::string currentShipType = "";
                std::string currentOrientation = "";
                Position currentPosition;

                std::vector<std::string> shipElements;
                std::string shipTypes[5] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};

                char contents[ship.size() + 1];
                std::strcpy(contents, ship.c_str());
                char* element = std::strtok(contents, ",");

                while (element != NULL) {

                    shipElements.push_back(element);

                    element = std::strtok(NULL, ",");
                }

                bool shipTypeResult = false;

                for (std::string shipType: shipTypes) {

                    if (shipElements[0] == shipType) { shipTypeResult = true; }
                }

                if (!shipTypeResult) {

                    throw InvalidShip();
                }
                else {

                    currentShipType = shipElements[0];
                }

                if (convertStringToPosition(shipElements[1]).getNumber() == 0) { throw InvalidPosition(); }
                else {

                    Position newPosition(convertStringToPosition(shipElements[1]).getLetter(), convertStringToPosition(shipElements[1]).getNumber());

                    currentPosition = newPosition;
                }

                char orientationElement = shipElements[2].at(0);

                if (toupper(orientationElement) == 'H') { currentOrientation = "H"; }
                else if (toupper(orientationElement) == 'V') { currentOrientation = "V"; }
                else { throw InvalidShipOrientation(); }

                Ship currentShip(currentShipType, currentPosition, currentOrientation);

                if (!verifyShipPlacement(currentShip, opponentShips)) {

                    throw InvalidShipPlacement();
                }
                else {

                    opponent.addShip(currentShip);
                    opponentShips.addShip(currentShip);
                }
            }

            opponentCreated = true;
        }
    }
    catch (FailedToOpenFile exception) {

        std::cout << "\t" << exception.what() << std::endl;

        std::chrono::seconds duration(1);
        std::this_thread::sleep_for(duration);

        return;
    }
    catch (InvalidShip exception) {

        std::cout << "\t" << exception.what() << std::endl;
        Player temp;
        opponent = temp;

        std::chrono::seconds duration(1);
        std::this_thread::sleep_for(duration);

        return;
    }
    catch (InvalidPosition exception) {

        std::cout << "\t" << exception.what() << std::endl;
        Player temp;
        opponent = temp;

        std::chrono::seconds duration(1);
        std::this_thread::sleep_for(duration);

        return;
    }
    catch (InvalidShipOrientation exception) {

        std::cout << "\t" << exception.what() << std::endl;
        Player temp;
        opponent = temp;

        std::chrono::seconds duration(1);
        std::this_thread::sleep_for(duration);

        return;
    }
    catch (InvalidShipPlacement exception) {

        std::cout << "\t" << exception.what() << std::endl;

        Player temp;
        opponent = temp;
        
        Grid newGrid;
        newGrid.initializeGridContents();
        opponentShips = newGrid;

        std::chrono::seconds duration(1);
        std::this_thread::sleep_for(duration);

        return;
    }
}

////////////////////////////////////////////////////////////
//      Play Player Strike
////////////////////////////////////////////////////////////

void Battleship::playPlayerStrike(Position position) {

    try {

        if (checkPositionValidity(position).getNumber() != 0) {

            if (!playerStrikes.checkStrike(position)) {

                throw StrikeAlreadyPlayed();
            }
            else {

                opponentShips.addStrike(position);
                playerStrikes.addStrike(position, opponentShips.getCharacterAtPosition(position));
                lastPlayerStrike = position;

                if (!checkWin()) {

                    playersTurn = false;
                    opponentsTurn = true;
                }
                else {

                    playersTurn = false;
                    opponentsTurn = false;
                    winner = true;
                    gameOver = true;
                }
            }
        }
    }
    catch (StrikeAlreadyPlayed exception) {

        std::cout << exception.what() << std::endl;

        std::chrono::seconds duration(1);
        std::this_thread::sleep_for(duration);
    }
}

////////////////////////////////////////////////////////////
//      Play Opponent Strike
////////////////////////////////////////////////////////////

void Battleship::playOpponentStrike() {

    char characters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    Position position(characters[rand() % 10], rand() % 10);

    if (checkPositionValidity(position).getNumber() != 0) {

        if (!opponentStrikes.checkStrike(position)) {

            playOpponentStrike();
        }
        else {

            playerShips.addStrike(position);
            opponentStrikes.addStrike(position, playerShips.getCharacterAtPosition(position));
            lastOpponentStrike = position;
            
            if (!checkWin()) {

                playersTurn = true;
                opponentsTurn = false;
            }
            else {

                playersTurn = false;
                opponentsTurn = false;
                loser = true;
                gameOver = true;
            }
        }
    }
}

////////////////////////////////////////////////////////////
//      Print Grid
////////////////////////////////////////////////////////////

void Battleship::printGrid(const std::string title, Grid grid) {

    std::cout << "\t*------------------------------*" << std::endl;
    std::cout << "\t*- " << title << " ";

    for (int i = 0; i < (27 - title.length()); i++) {

        std::cout << "-";
    }

    std::cout << "*" << std::endl;
    std::cout << "\t*------------------------------*" << std::endl;
    std::cout << "\t   A B C D E F G H I J" << std::endl;
    grid.printContents();
    std::cout << "\t*------------------------------*" << std::endl;
}

////////////////////////////////////////////////////////////
//      Private Functions
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//      Verify Ship Placement
////////////////////////////////////////////////////////////

bool Battleship::verifyShipPlacement(Ship ship, Grid grid) {

    bool result = true;

    char** gridContents = grid.getContents();

    int coordinateCount = 0;
    std::vector<int> xCoordinates;
    std::vector<int> yCoordinates;

    int currentX, currentY;

    int shipLength = ship.getShipLength();
    Position position = ship.getPosition();
    std::string orientation = ship.getOrientation();

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

        if ((xCoordinates[i] < 0) || (xCoordinates[i] > 9)) { result = false; }
        else if ((yCoordinates[i] < 0) || (yCoordinates[i] > 9)) { result = false; }
        else if (gridContents[yCoordinates[i]][xCoordinates[i]] != '~') { result = false; }
    }

    return result;
}

////////////////////////////////////////////////////////////
//      Check Win
////////////////////////////////////////////////////////////

bool Battleship::checkWin() {

    bool playerResult = true;
    bool opponentResult = true;

    for (int i = 0; i < 10; i++) {

        for (int j = 0; j < 10; j++) {

            if (
                
                playerShips.getContents()[i][j] != '~' && 
                playerShips.getContents()[i][j] != 'H' && 
                playerShips.getContents()[i][j] != 'M'
            ) {

                playerResult = false;
            }

            if (
                
                opponentShips.getContents()[i][j] != '~' && 
                opponentShips.getContents()[i][j] != 'H' && 
                opponentShips.getContents()[i][j] != 'M'
            ) {

                opponentResult = false;
            }
        }
    }

    if (playerResult || opponentResult) { return true; }
    else { return false; }
}