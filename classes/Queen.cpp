#include "Queen.hpp"

char Queen::getsymbol(){ 
  return (getcolor() == Color::WHITE) ? 'Q' : 'q'; 
}