/*
  ------------------------------Librerias a usar---------------------------------
*/

/*
  ------------------------------Fin de librerias---------------------------------
*/

/*
  ------------------------------Pines usados-------------------------------------
*/

/*
  ------------------------------Fin de pines usados-------------------------------
*/

/*
  ------------------------------Variables a utilizar------------------------------
*/

/*  
 *   Variable que controla lo que envia la aplicacion Android.
 *   Tendra los siguientes valores dependiendo de que boton
 *   presionen en la aplicacion:
 *      0 = ARRIBA
 *      1 = ABAJO
 *      2 = DERECHA
 *      3 = IZQUIERDA
 *      4 = BARRER
 *      5 = LIMPIAR MEMORIA
 */
int state = -1;
bool modoAutomatico = true;

/*
  ------------------------------Fin de variables----------------------------------
*/

void adelante(){
  
}

void atras(){
  
}

void derecha(){
  
}

void izquierda(){
  
}

void barrer(){
  
}

void loopAutomatico(){
  /* Primero se detectan los colores para ver si se debe de realizar alguna accion especifica
     como la de barrer, volverse a modo manual o retroceder y girarse.
     Luego si no se debe de realizar alguna accion especial se debe de detectar si hay obstaculos
     para esquivar hacia la derecha o a la izquierda.
     Ya si no pasa nada de eso que se mueva para adelante xd
   */
}

void loopManual(){
  /*
    Solo debe de detectar la accion que le envia el telefono y realizar el movimiento correspondiente
  */
}

void setup() {

  Serial.begin(9600);

}

void loop() {

  if(modoAutomatico){
    loopAutomatico();
  }else{
    loopManual();
  }

}

/*

    Flujo de la aplicacion

-------------MODO AUTOMATICO-------------
El robot iniciara en el modo automatico. Este debe de estar detectando objetos todo el rato.
Debe de poder evadir por la izquierda y por la derecha. Este deberá de poder moverse solo
dentro de los limites de la pista, considerando limite por pared o por gradas.
En modo automatico aparte de moverse todo el rato para adelante y barrer debe de detectar 
los siguientes colores y realizar la accion correspondiente:
    Rojo: Barrer
    Azul: Modo Manual
    Negro: Retroceder y girarse
Para cambiar al modo manual tambien se necesita de un boton en el robot.

-------------MODO MANUAL-------------
Este modo solo debe de estar leyendo las salidas de la aplicacion asi como mandar a la aplicacion
las rutas que se han guardado en el EEPROM. Tambien se le deberá de poder enviar rutas a elegir
Tambien existira la opción limpiar rutas que borrara la memoria EEPROM del arduino.

*/
