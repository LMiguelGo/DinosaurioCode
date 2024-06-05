#include <LiquidCrystal.h>
#include "Dinosaurio.h";
#include "Cactus.h";
#include "Terodaptilo.h";

LiquidCrystal lcd(22,23,5,18,19,21);
Dinosaurio dino;
Cactus cactus(16);
Terodaptilo tero;

byte dinoReposo[8] = {
  B00000,
  B00000,
  B00111,
  B00101,
  B10111,
  B10100,
  B01101,
  B01100
};
byte dinoCamina1[8] = {      
  B00000,
  B00111,
  B00101,
  B10111,
  B10100,
  B01110,
  B01100,
  B00010
};  
byte dinoCamina2[8] = {
  B00000,
  B00111,
  B00101,
  B10111,
  B10100,
  B01110,
  B01100,
  B10000
};
byte dinoSalta[8] = {      
  B00111,
  B00101,
  B10111,
  B10100,
  B01101,
  B01100,
  B10000,
  B00000
};
byte cactus1[8] = {      
  B00000,
  B00000,
  B00001,
  B10101,
  B01101,
  B00110,
  B00100,
  B00100
};
byte terodaptilo[8] = {
  B00000,
  B00000,
  B00001,
  B10101,
  B01101,
  B00110,
  B00100,
  B00100
};

bool gameover = false;
int velocidad = 300;
int puntuacion = 0;

//Variables para generacion aleatoria de cactus
int contadorC = 0;
int aleatorioCactus = 0;
int tiempo = 0;

//Variables para generacion aleatoria de terodactilo
int contadorT = 0;
int aleatorioTero = 0;

struct Button {
  const uint8_t PIN;
  bool pressed;
};

Button button1 = {4, false};

void IRAM_ATTR isr() {  
  button1.pressed = true;  
}

//-----------------------------------------------------
void setup() {
  
  lcd.begin(16, 2); 
  Serial.begin(115200);
  Serial.println("test");

  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr, FALLING);

  lcd.createChar(0, dinoReposo);
  lcd.createChar(1, dinoCamina1);
  lcd.createChar(2, dinoCamina2);
  lcd.createChar(3, dinoSalta);
  lcd.createChar(4, cactus1);
  lcd.createChar(5, terodaptilo);

  lcd.setCursor(0, 1);
  lcd.write(byte(0));  

  delay(4000);  
}

void loop() {
  if (gameover == false){
    // Se borra la pantalla
    lcd.clear();

    // Se pinta la pantalla
    if (button1.pressed) {      
      dino.saltar();
      lcd.setCursor(0, 0);
      button1.pressed = false;      
    }
    else {
      lcd.setCursor(0, 1);
      dino.caminar();    
    }     
    
    lcd.write(byte(dino.obtenerEstado()));  
    generarEnemigos();

    // Comprobar la colision
    if(dino.obtenerPosicion() == 0 && cactus.obtenerPosicion() == 0) {
      Serial.println("Colision!");
      gameover = true;
    }

    puntuacion = puntuacion + 1; 

    delay(velocidad); 

  }else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GAME OVER");
    lcd.setCursor(0,1);
    lcd.print("Score: " + String(puntuacion));
    delay(velocidad);

    if (button1.pressed) {
      gameover = false; 
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("TRY AGAIN");
      delay(1000);
    }
  }
}

void generarEnemigos(){
  tiempo = tiempo + 1;
  if (tiempo == 15){
    tiempo = 0;
  }

  //Generación aleatoria de Cactus
  if (contadorC < 16){
    cactus.mover();
    lcd.setCursor(cactus.obtenerPosicion(),1);
    lcd.write(byte(4));
    contadorC  = contadorC + 1;
    aleatorioCactus = random(16);
  }else{   
    cactus.setPosicionInicial(16);
    if(tiempo==aleatorioCactus){
      contadorC = 0;
    }
  }

  //Generacion aleatoria de Terodactilo
  if (contadorT < 16){
    tero.mover();
    lcd.setCursor(tero.obtenerPosicion(),1);
    lcd.write(byte(5));
    contadorT  = contadorT + 1;
    aleatorioTero = random(16);
  }else{   
    tero.setPosicionInicial(16);
    if(tiempo==aleatorioTero){
      contadorT = 0;
    }
  }
}
