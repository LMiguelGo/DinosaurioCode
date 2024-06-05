//Definir clase en caso de que no esté definida
#ifndef Terodaptilo_h
#define Terodaptilo_h
#include  "Arduino.h"

class Terodaptilo {
  private: //Atributos
    int x;

  public: //Métodos
    Terodaptilo();//constructor
    int obtenerPosicion();
    void mover();
    void setPosicionInicial(int posicionInicial);
};

#endif
