#include"Knight.hpp"

string Knight::getsymbol()
{
    if (getcolor() == Color::WHITE)
        return "♘";
    else
        return "♞";
}