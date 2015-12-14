#ifndef COLOR_H
#define COLOR_H

#include <string>

using std::string;

enum class EColor : unsigned char
{
    Red   = 1,
    Green = 2,
    Blue  = 3
};

string ColorToString(EColor color);

bool ParseColor(const string& colorString, EColor& color);

#endif
