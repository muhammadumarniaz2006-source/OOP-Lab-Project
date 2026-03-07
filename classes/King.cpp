#include "King.hpp" 

string King::getsymbol()
{
    if (getcolor() == Color::WHITE)
        return "♔";
    else
        return "♚";
}