#include "King.hpp" 

char King::getsymbol() { 
  return (getcolor() == Color::WHITE) ? 'K' : 'k'; 
}