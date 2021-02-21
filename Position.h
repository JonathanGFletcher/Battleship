#ifndef POSITION_H
#define POSITION_H

class Position {

private:

    char letter;
    int number;

public:

    Position();
    Position(char, int);

    Position& operator=(Position&);
    bool operator==(Position&);

    const char& getLetter();
    const int& getNumber();
};

#endif