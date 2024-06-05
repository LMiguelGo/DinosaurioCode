#include "Terodaptilo.h"

//Se construye el objeto dandole valores iniciales
Terodaptilo::Terodaptilo() {
  x = 8;
}

int Terodaptilo::obtenerPosicion(){
  return x;
}

void Terodaptilo::mover(){
  if(x > 0) {
    x = x - 1;
  }else{
    x = 15;
  }
}

void Terodaptilo::setPosicionInicial(int posicionInicial){
  x = posicionInicial;
}
