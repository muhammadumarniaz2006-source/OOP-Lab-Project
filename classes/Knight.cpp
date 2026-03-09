#include"Knight.hpp"

char Knight::getsymbol(){
  return (getcolor() == Color::WHITE) ? 'N' : 'n'; 
}