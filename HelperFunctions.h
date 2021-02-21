#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <string>

#include "Position.h"

int convertLetterToNumber(const char&);
Position convertStringToPosition(const std::string&);
Position checkPositionValidity(Position);

#endif