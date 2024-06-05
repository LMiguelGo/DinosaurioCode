#include "Cactus.h"

Cactus::Cactus(int posicionInicial) {  
  x = posicionInicial;  
}

void Cactus::mover() {   
  if(x > 0) {
    x = x - 1;
  }else{
    x = 15;
  }
}

int Cactus::obtenerPosicion() {
  return x;
}

void Cactus::setPosicionInicial(int posicionInicial){
  x = posicionInicial;
}
