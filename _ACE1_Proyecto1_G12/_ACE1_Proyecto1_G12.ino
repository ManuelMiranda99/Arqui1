/*
  ------------------------------Librerias a usar---------------------------------
*/



/*
  ------------------------------Fin de librerias---------------------------------
*/

/*
  ------------------------------Pines usados-------------------------------------
*/

// Pin de la bocina
//#define BOCINA 

// Pines de movimiento
  // Movimiento en X
//#define XPOS
//#define XNEG
  // Movimiento en Y
//#define YPOS
//#define YNEG
  // Movimiento en Z
//#define Z
  // Soltar garra
//#define G  

/*
  ------------------------------Fin de pines usados-------------------------------
*/

/*
  ------------------------------Variables a utilizar------------------------------
*/

int cCoin = 0;
int xPos = 0, yPos = 0;
boolean bLoopMecanico = false;
boolean bLoopApp = false;
boolean peluche = false;

/*
  ------------------------------Fin de variables----------------------------------
*/

void detectarMoneda(){
  /*
    Si detecta una moneda de 25c sumarle 25 a cCoin
    Si detecta una moneda de 50c sumarle 50 a cCoin
    Si detecta una moneda de 1Q sumarle 100 a cCoin
  */

  // Se envia a la aplicacion el valor de cCoin
  Serial.println(cCoin);
}

void xPos(){
  
}

void xNeg(){
  
}

void yPos(){
  
}

void yNeg(){
  
}

boolean zMov(){
  
}

void Garrra(){
  
}

void detectarPeluche(){
  
}

void loopMecanico(){
  // +X
  if(digitalRead(XPOS)==HIGH){
    xPos();
  }
  // -X
  else if(digitalRead(XNEG)==HIGH){
    xNeg();
  }
  // +Y
  else if(digitalRead(YPOS)==HIGH){
    yPos();
  }
  // -Y
  else if(digitalRead(YNEG)==HIGH){
    yNeg();
  }
  // Z
  else if(digitalRead(Z)==HIGH){
    // Guardo en la variable peluche si agarro o no el peluche
    peluche = zMov();

    if(peluche){
      pintarMatriz('T');
    }else{
      pintarMatriz('L');

      regresarPos();

      Serial.print("GAME OVER");

      fin();
      
    }
    
  }
  // Soltar garra
  else if(digitalRead(G)==HIGH){
    Garra();

    detectarPeluche();
    
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
    else if(result == 4){
      // Guardo en la variable peluche si agarro o no el peluche
      peluche = zMov();

      if(peluche){
        pintarMatriz('T');
      }else{
        pintarMatriz('L');

        regresarPos();

        Serial.print("GAME OVER");

        fin();
        
      }
      
    }
    // Soltar garra
    else if(result == 5){
      Garra();

      detectarPeluche();
      
    }
  }
}

// Setea las variables de inicio a sus valores originales
void fin(){
  peluche = false;
  bLoopMecanico = false;
  bLoopApp = false;
  cCoin = 0;
}

// Metodo para limpiar la matriz
void pintarMatriz(char _c){
  // Pintar matriz de forma normal
  if(_c == 'N'){
    
  }
  // Pintar matriz y dejarla titiritando la posicion correcta
  else if(_c == 'T'){
    
  }
  // Sin tomar el peluche
  else if(_c == 'L'){
    
  }
}

void setup() {
  
  Serial.begin(9600);
  
  // Setup de bocina
  pinMode(BOCINA, OUTPUT);

  // Inicializacion de bocina
  digitalWrite(BOCINA, LOW);
}

void loop() {

  pintarMatriz('N');

  if(bLoopMecanico){
    loopMecanico();
  }
  
  if(bLoopApp){
    loopApp();
  }

  if(!bLoopMecanico && !bLoopApp){
    
    detectarMoneda();
    
    // Si ingreso la cantidad adecuada de monedas
    if(cCoin == 100){

      Serial.print("1");
      digitalWrite(BOCINA, HIGH);
      delay(1500);
      digitalWrite(BOCINA, LOW);
      
      // Ver la señal que envia la App al arduino
      if(Serial.available()>0){
        int result = Serial.read();
  
        
        // Si ingreso al modo mecanico
        if(result == 0){
          bLoopMecanico = true;
        }
        
        // Si ingreso al modo aplicacion
        else if(result == 1){
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
