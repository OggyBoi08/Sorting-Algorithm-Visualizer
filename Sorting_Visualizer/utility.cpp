#include "utility.h"
#include <stdexcept>


Colour hexToColour(std::string hex_code)
{
    if (hex_code[0]=='#')
        hex_code = hex_code.substr(1);   //substring starts from 1
    if (hex_code.length()!=6)
        throw std::invalid_argument("*** Invalid Hex Colour ***");

    Colour colour;

    colour.r = std::stoi(hex_code.substr(0,2), nullptr, 16);
    colour.g = std::stoi(hex_code.substr(2,2), nullptr, 16);
    colour.b = std::stoi(hex_code.substr(4,2), nullptr, 16);

    return colour;
}
