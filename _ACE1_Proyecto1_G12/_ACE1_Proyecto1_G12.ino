/*
  ------------------------------Librerias a usar---------------------------------
*/
// Libreria de matriz de LEDs
#include "LedControl.h"
LedControl lc = LedControl(10,11,12,1);

// Libreria de servomotor
#include <Servo.h>
Servo servo;

/*
  ------------------------------Fin de librerias---------------------------------
*/

/*
  ------------------------------Pines usados-------------------------------------
*/

  // Pin de la bocina
#define BOCINA 9
  // Pin para confirmar agarre
#define CONFIRMO A6
  // Pin del tobogan
#define TOBOGAN A2
// Pines de movimiento
  // Movimiento en X
#define XPOS 31
#define XNEG 32
  // Movimiento en Y
#define YPOS 33
#define YNEG 34
  // Movimiento en Z
#define Z 35 
  // Movimiento Garra
#define G 36
  // Motor Z
#define ZPOS 37
#define ZNEG 38
  // Soltar garra (Servo)
#define GARRA 39
  //Pines del contador de fichas
#define QUETZAL A5
#define CINCUENTA A3
#define VEINTICINCO A4

/*
  ------------------------------Fin de pines usados-------------------------------
*/

/*
  ------------------------------Variables a utilizar------------------------------
*/

int cCoin = 0;
int x = 0, y = 0;
boolean bLoopMecanico = false;
boolean bLoopApp = false;
boolean peluche = false;

const int fila[8] = {
  22, 32, 31, 28, 45, 33, 43, 37
};
const int columna[8] = {
  30, 41, 39, 24, 35, 26, 34, 36
};

byte tablero[8][8] =
  {  { 1,0,0,0,0,0,0,0 },    // 0
     { 0,0,0,0,0,0,0,0 },    // 1
     { 0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0 },
 };

// Musica
float c[5]={131,262,523.25,1046.50,2093.01};       // frecuencias 4 octavas de Do
float cs[5]={139,277,554,1108,2217};      // Do#
float d[5]={147,294,587.33,1174.66,2349};       // Re
float ds[5]={156,311,622,1244,2489};    // Re#
float e[5]={165,330,659.26,1318.51,2637};      // Mi
float f[5]={175,349,698.46,1396.91,2794};       // Fa
float fs[5]={185,370,740,1480,2960};     // Fa#
float g[5]={196,392,783.99,1567.98,3136};     // Sol
float gs[5]={208,415,831,1661,3322};   // Sol#
float a[5]={220,440,880,1760,3520};      // La
float as[5]={233,466,932,1866,3729};    // La#
float b[5]={247,494,987.77,1975.53,3951};      // Si
// Fin de musica


/*  
    Bandera para controlar si bajo la garra o no. Si no la ha bajado se mantiene en true 
    y esta desactivado boton de abrir. Si esta en falso, ya bajo y esta desactivado el boton de bajar
*/
bool noBajo = true;

/*
  ------------------------------Fin de variables----------------------------------
*/

// Funcion para tocar una nota especifica
void nota(float frec, float t){
  tone(BOCINA, frec);
  delay(t);
}

// Cancion para despues de ingresar notas correctas
void bocina(){
  nota(f[3], 250);          
  nota(a[3], 250); 
  nota(b[3], 500);
  
  nota(f[3], 250);          
  nota(a[3], 250); 
  nota(b[3], 500);
  
  nota(f[3], 250);          
  nota(a[3], 250); 
  nota(b[3], 250);
  nota(e[4],250);
  nota(d[4],500); 
   
  nota(b[3],250);
  nota(c[4],250);
  nota(b[3],250 );
  nota(g[3],250 );
  nota(e[3],750 );
      
  
  nota(d[3], 250);
  nota(e[3],250);
  nota(g[3], 250);
  nota(e[3],500);
  noTone(BOCINA);
}

void pintarLed(){

  byte together = 0;
    for (int k = 0; k < 8; k++){
      for (int i = 0; i < 8; i++){
       together += (tablero[i][k] << (7-i));
      }
      lc.setRow(0, k, together);
      together=0;
    } 
}

// Encender una posicion especifica en la matriz de LEDs
void encenderPos(int x, int y){
  tablero[x][y]=1;
}

// Apagar una posicion especifica en la matriz de LEDs
void apagarPos(int x, int y){
  tablero[x][y]=0;
}

byte triste[8][8]={  
     { 1,0,0,0,0,0,0,1 },    // 0
     { 0,1,1,0,0,1,1,0 },    // 1
     { 0,0,0,1,1,0,0,0 },
     { 0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0 },
     { 0,0,1,0,0,1,0,0 },
     { 0,0,1,0,0,1,0,0 },
     { 0,0,1,0,0,1,0,0 },
 };
// Pintar cara triste en matriz de leds cuando pierda el jugador
void caraTriste(){

  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      tablero[i][j] = triste[i][j];
    }
  }

  pintarLed();
}

byte feliz[8][8]={  
     { 0,0,0,1,1,0,0,0 },    // 0
     { 0,0,1,0,0,1,0,0 },    // 1
     { 0,1,0,0,0,0,1,0 },
     { 1,0,0,0,0,0,0,1 },
     { 0,0,0,0,0,0,0,0 },
     { 0,0,1,0,0,1,0,0 },
     { 0,0,1,0,0,1,0,0 },
     { 0,0,1,0,0,1,0,0 },
 };
void caraFeliz(){
  
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      tablero[i][j] = feliz[i][j];
    }
  }

  pintarLed();
}

// Funcion que detecta la moneda ingresada
void detectarMoneda(){

  // Se guarda en variables los valores que sacan los sensores
  int Quetzal = analogRead(A5);
  int Cincuenta = analogRead(A3);
  int Venticinco = analogRead(A4);

  // Ingreso ficha de quetzal
  if(Quetzal > 1000){
    cCoin+=100; 
    Serial.print(100);
  }

  // Ingreso ficha de cincuenta
  if(Cincuenta > 1000){
    cCoin+=50; 
    Serial.print(50);
  }

  // Ingreso ficha de venticinco
  if(Venticinco > 1000){
    cCoin+=25; 
    Serial.print(25);
  }
  
}

// Movimiento positivo en X
void xPos(){
  x++;
  encenderPos(x,y);
  digitalWrite(XNEG,HIGH);
  delay(77);
  digitalWrite(XNEG,LOW);
}

// Movimiento negativo en X
void xNeg(){
  encenderPos(x,y);
  x--;
  digitalWrite(XPOS,HIGH);
  delay(70);
  digitalWrite(XPOS,LOW);
}

// Movimiento positivo en Y
void yPos(){
  encenderPos(x,y);
  y--;
  digitalWrite(YPOS, HIGH);
  delay(500);
  digitalWrite(YPOS, LOW);
}

// Movimiento negativo en Y
void yNeg(){
  y++;
  encenderPos(x,y);
  digitalWrite(YNEG, HIGH);
  delay(1000);
  digitalWrite(YNEG, LOW);
}

boolean zMov(){
  for(int i=0;i<3;i++){
    // Bajar la garra
    digitalWrite(ZPOS, LOW);
    digitalWrite(ZNEG, HIGH);
    delay(55);
    // Parar la garra
    digitalWrite(ZPOS, LOW);
    digitalWrite(ZNEG, LOW);
    delay(500);
  }
  /*Agarre de la garra*/
  bool agarro = true;

  // Movimiento de garra por medio de delays para no ser tan brusco. Desde 90 hasta 0
  for(int i = 90; i > -1 ; i--){
    servo.write(i);
    delay(10);
  }

  // Variable que detecta si agarro el peluche o no
  int detector = analogRead(CONFIRMO);

  if(detector > 1000){
    agarro = true;
  }else{
    agarro = false;
  }

  for(int i=0;i<10;i++){
    // Subir la garra
    digitalWrite(ZPOS, HIGH);
    digitalWrite(ZNEG, LOW);
    delay(80);
    digitalWrite(ZPOS, LOW);
    digitalWrite(ZNEG, LOW);
    delay(500);
  }

  return agarro;
}

// Funcion para soltar garra
bool Garra(){
  // Soltar garra con delays para que no sea tan brusco. Desde 0 hasta 90
  for(int i=0; i <= 90; i++){
    servo.write(i);
    delay(10);
  }
}

// Funcion que detecta si paso o no un peluche por el tobogan
bool detectarPeluche(){
  int detector;
  for(int i=0;i<1000;i++){
    detector = analogRead(TOBOGAN);

    // Si llega a detectar algo lanza true
    if(detector > 1000){
      return true;
    }
    
    delay(100);
  }
  // Si no detecta nada lanza false
  return false;
}

// Funcion para regresar a posicion original
void regresarPos(){
  
}

// Setea las variables de inicio a sus valores originales
void fin(){
  peluche = false;
  bLoopMecanico = false;
  bLoopApp = false;
  noBajo = true;
  cCoin = 0;
}

/*
  ------------------------------------------------------------------------
  --------------------------Parte de loops--------------------------------
  ------------------------------------------------------------------------
*/

void loopMecanico(){

  /*
   * Tomar nota que X y x no son lo mismo, mismo caso aplica para Y y y, siendo los primeros de cada uno el valor analógico
   */
  pintarLed();
  int X = analogRead(A0); 
  int Y = analogRead(A1);


  // +X
  if (X > 800 && X <= 1023){ 
    if(x<7){
      xPos();
    }
  }
  // -X
  else if(X >= 0 && X < 200){
    if(x>0){
      xNeg();
     }
  }
  // +Y
  else if(Y > 800 && Y <= 1023){
    if(y>0){
      yPos();
    }
  }
  // -Y
  else if(Y >= 0 && Y < 200){
    if(y<7){
      yNeg();
    }
  }
  // Z
  else if(digitalRead(Z)==HIGH && noBajo){
    noBajo = false;
    // Guardo en la variable peluche si agarro o no el peluche. ZMov es el movimiento automatico de bajar la garra y agarrar un peluche
    peluche = zMov();        
  }
  // Soltar garra
  else if(digitalRead(G)==HIGH && !noBajo){

    Garra();

    bool estado=detectarPeluche();
    delay(200);
    if(estado=true){
      Serial.print(1); 
      caraFeliz();
    }else{
      Serial.print(0);
      caraTriste();
    }
  }
}



void loopApp(){
  if(Serial.available()>0){
    int result = Serial.read();

    // +X
    if(result == 0){
      xPos();
    }
    // -X
    else if(result == 1){
      xNeg();
    }
    // +Y
    else if(result == 2){
      yPos();
    }
    // -Y
    else if(result == 3){
      yNeg();
    }
    // Bajar garra
    else if(result == 4 && noBajo){
      noBajo = false;
      // Guardo en la variable peluche si agarro o no el peluche
      peluche = zMov();  
      
    }
    // Soltar garra
    else if(result == 5 && !noBajo){
      
      Garra();

      bool estado=detectarPeluche();
      delay(200);
      if(estado=true){
        Serial.print(1); 
        caraFeliz();
      }else{
        Serial.print(0);
        caraTriste();
      }
    }
  }
}

void setup() {
  
  Serial.begin(9600);
  
  // Setup de bocina
  pinMode(BOCINA, OUTPUT);

  //Setup de la matriz

  lc.shutdown(0,false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  //Pines para los carriles de impresora
  pinMode(XPOS,OUTPUT);
  pinMode(XNEG,OUTPUT);
  digitalWrite(XNEG, LOW);
  digitalWrite(XPOS, LOW);

  pinMode(YPOS,OUTPUT);
  pinMode(YNEG,OUTPUT);
  digitalWrite(YNEG, LOW);
  digitalWrite(YPOS, LOW);

  // Pines del motor que baja la garra
  pinMode(ZPOS, OUTPUT);
  pinMode(ZNEG, OUTPUT);
  digitalWrite(ZPOS, LOW);
  digitalWrite(ZNEG, LOW);

  // Pin de boton de bajar garra
  pinMode(Z, INPUT);

  digitalWrite(Z, LOW);

  // Pin de boton para soltar la garra
  pinMode(G, INPUT);

  digitalWrite(G, LOW);

  // Pines para la garra (servo)
  pinMode(GARRA, OUTPUT);
  // Falta inicializacion del servo
  
  for(int i=0;i<=90;i++){
    servo.write(i);
    delay(10); 
  }
  
}

void loop() {

  // Si la bandera de loop mecanico esta prendida, entrar a loopMecanico
  if(bLoopMecanico){
    loopMecanico();
  }

  // Si la bandera de loop app esta prendida, entrar a loopApp
  if(bLoopApp){
    loopApp();
  }

  // Si ninguna de las banderas esta activa, entrar a detectar monedas
  if(!bLoopMecanico && !bLoopApp){
    
    detectarMoneda();
    
    // Si ingreso la cantidad adecuada de monedas
    if(cCoin >= 100){
      //cCoin=0;
      bocina();
      delay(100);
      // Ver la señal que envia la App al arduino para decidir el tipo de manejo de maquina
      if(Serial.available()>0){
        char result = Serial.read();
  
        
        // Si ingreso al modo mecanico
        if(result == '0'){
          bLoopMecanico = true;
        }
        
        // Si ingreso al modo aplicacion
        else if(result == '1'){
          bLoopApp = true;
        }
        
      }
    }
  }
}

/*
            Botones necesarios para el funcionamiento de la maquina
- Boton para movimiento X+
- Boton para movimiento X-
- Boton para movimiento Y+
- Boton para movimiento Y-
OJO: El tema de los movimientos XY también se pueden (o quizá deben) ir por medio de una 
palanca. Si es así igual trendrían que haber 4 botones y con la palanca presionarlos.
- Boton para movimiento automatico en Z
- Boton para que la maquina suelte el peluche
            Flujo de la Aplicacion
Primero se debe de detectar que ingresen las fichas necesarias para llegar a 1Q. Se podran
ingresar monedas de 0.25Q, 0.50Q y 1Q. Cuando llegue al valor necesario (1Q) dentro de la
aplicación debe de sonar algo y luego se debe de seleccionar el modo de uso de la garra. 
Existiran dos tipos:
  - Modo mecánico
  - Modo aplicación
En ambos modos se siguen los mismos movimientos, solamente se usarán distintos modos de enviar
señales a el arduino. Cuando el usuario quiera bajar la garra esta debe de bajar automaticamente
para intentar agarrar el peluche u objeto. Esto quiere decir que cuando se presione el botón
de bajar la garra ocurrirán tres movimientos automaticos: Movimiento de bajada en Z. Movimiento
para cerrar la garra para agarrar el peluche. Y movimiento de subida. Durante el movimiento
de la garra debe de mostrarse el camino de la garra en una matriz de LEDs.
Cuando el usuario pida que baje la garra habrán dos casos:
- Si agarra el peluche: 
Si consigue el peluche, en la matriz de LEDs debe de quedar titiritando
la posición donde se consiguió el peluche. 
También si se da este caso los movimientos siguientes deben de realizarse de
manera manual, quiere decir que el usuario debe de llevar la garra hasta el tobogán. Si se 
lográ llevar el peluche al tobogán se deberá de enviar un mensaje de felicitaciones a la aplicación
Android. 
- Si no agarra el peluche: 
En este caso la matriz de LEDs debe de borrarse el rastro de la garra y debe de mostrarse una
cara triste en la matriz de LEDs.
Si sucede este caso debe de regresar la garra a su posición inicial,
es decir, encima del tobogán de manera automática. Cuando no agarre el peluche se debe de mandar
un mensaje de Game Over a la aplicación Android. 
Se debe de tener una puerta en el tobogán. En caso se logre dejar el peluche en el tobogán
Se debe de abrir esta puerta. En caso contrario siempre permanecerá cerrada. 
*/
