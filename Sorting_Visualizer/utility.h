#ifndef UTILITY_H
#define UTILITY_H

#include <string>


struct Colour
{
    int r,g,b;
};

Colour hexToColour(std::string hex_code);


#endif // UTILITY_H
