#include "color.h"

string ColorToString(EColor color)
{
    string colorString = "unknown";

    switch (color)
    {
        case EColor::Red   : colorString = "red"; break;
        case EColor::Green : colorString = "green"; break;
        case EColor::Blue  : colorString = "blue"; break;
    }

    return colorString;
}

bool ParseColor(const string& colorString, EColor& color)
{
    if (colorString == "red")
    {
        color = EColor::Red;
        return true;
    }
    else if (colorString == "green")
    {
        color = EColor::Green;
        return true;
    }
    else if (colorString == "blue")
    {
        color = EColor::Blue;
        return true;
    }

    // error
    return false; 
}
