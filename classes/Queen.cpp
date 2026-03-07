#include "Queen.hpp"
string Queen::getsymbol()
{
    if (getcolor() == Color::WHITE)
        return "♕";
    else
        return "♛";
}