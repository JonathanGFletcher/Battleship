#include <iostream>
#include <stdexcept>

class FailedToStartGame : public std::exception {

public:

    const char* what() {

        return "Game is not setup to start.";
    }
};

class StrikeAlreadyPlayed : public std::exception {

public:

    const char* what() {

        return "The desired strike has already been played.";
    }
};

class InvalidShip : public std::exception {

public:

    const char* what() {

        return "Invalid ship.";
    }
};

class InvalidShipPlacement : public std::exception {

public:

    const char* what() {

        return "Placement of ship is invalid.";
    }
};

class InvalidShipOrientation : public std::exception {

public:

    const char* what() {

        return "Invalid ship orientation provided.";
    }
};

class InvalidPosition : public std::exception {

public:

    const char* what() {

        return "Invalid position provided.";
    }
};

class IntersectingShips : public std::exception {

public:

    const char* what() {

        return "No ship orientation was specified.";
    }
};

class FailedToOpenFile : public std::exception {

public:

    const char* what() {

        return "Failed to open file.";
    }
};