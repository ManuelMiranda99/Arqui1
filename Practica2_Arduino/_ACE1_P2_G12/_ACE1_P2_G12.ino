/*
  ------------------------------Librerias a usar---------------------------------
*/
#include <Servo.h>                // Libreria de Servo (Grados)
#include <LiquidCrystal.h>        // Libreria de pantalla LCD
/*
  ------------------------------Fin de librerias---------------------------------
*/

/*
  ------------------------------Pines usados-------------------------------------
*/
// Servo
#define SERVOPIN                  // Pin del servo
#define REC1 90                   // Constante de recipiente 1
#define REC2 120                  // Constante de recipiente 2
#define REC3 45                   // Constante de recipiente 3
// LCD
#define RS                        // Pin RS para LCD
#define EN                        // Pin EN para LCD
#define D4                        // Pin de Data Bit 4
#define D5                        // Pin de Data Bit 5
#define D6                        // Pin de Data Bit 6
#define D7                        // Pin de Data Bit 7
// Ultrasonico
#define TRIGGERUS 2                // Pin para el Trigger de sensor
#define ECHO 3                     // Pin para el Echo del sensor
//Sensor de color
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define SOut 5


/*
  ------------------------------Fin de pines usados-------------------------------
*/

/*
  ------------------------------Variables a utilizar------------------------------
*/
// Lugar para meter variables nosotros \>:V/
int productosTotales = 0, productosR1 = 0, productosR2 = 0, productosR3 = 0;
int distanciaRecorrida=100;
int rojo=0;
int verde=0;
int azul=0;

// Lugar de objetos y variables necesarias para los motores \>:V/
Servo servo;
//LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
/*
  ------------------------------Fin de variables----------------------------------
*/

/*
Meter código para mover el motor y validaciones de tamaño y color. Junto con la validación
de tamaño debe de verificar si esta pasando un producto o no.
*/
void transportar(){
  digitalWrite(TRIGGERUS,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERUS,LOW);
  int tiempo=pulseIn(ECHO,HIGH);
  distanciaRecorrida=tiempo/59;

  Serial.print("Distancia: ");
  Serial.print(distanciaRecorrida);
  Serial.print("cm");
  Serial.println();
  delay(10);
    
}

// Metodo a llamar para mover servomotor cierta cantidad de grados
void moverServo(int _grados){
  servo.write(_grados);
}
//Metodo a llamar para sensor de color
void detectarColor(){
  color();
  Serial.print("   ");
  Serial.print(rojo,DEC);
  Serial.print("   ");
  Serial.print(verde,DEC);
  Serial.print("   ");
  Serial.print(azul,DEC);

  if (rojo < azul && verde > azul && rojo < 35) 
  {  
   Serial.println("   Rojo");    
  }   
  else if (azul < rojo && azul < verde && verde < rojo)  
  {  
   Serial.println("   Azul");        
  }  

  else if (rojo > verde && azul > verde )  
  {  
   Serial.println("   Verde");       
  }  
  else{
  Serial.println("  ");  
  }
  delay(1000);     
  }  
    
  
  

void color(){
  digitalWrite(S3, LOW);  
  digitalWrite(S4, LOW);   
  rojo = pulseIn(SOut, digitalRead(SOut) == HIGH ? LOW : HIGH);  
  digitalWrite(S4, HIGH);   
  azul = pulseIn(SOut, digitalRead(SOut) == HIGH ? LOW : HIGH);  
  digitalWrite(S3, HIGH);    
  verde = pulseIn(SOut, digitalRead(SOut) == HIGH ? LOW : HIGH);  
  
  }
void setup() {

  // Iniciamos comunicacion. Saber ni porque va esto :v
  Serial.begin(9600);

  // Setup de Ultrasonico
  pinMode(TRIGGERUS, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIGGERUS, LOW);

  // Setup de Servo
//  servo.attach(SERVOPIN);
  // Mover servo a posición de Recipiente 1
  moverServo(90);

  // Setup de LCD
 // lcd.begin(16, 2);

 //Setup del sensor de color
 pinMode(S1,OUTPUT);
 pinMode(S2,OUTPUT);
 pinMode(S3,OUTPUT);
 pinMode(S4,OUTPUT);
 pinMode(SOut,INPUT);

 digitalWrite(S1,HIGH);
 digitalWrite(S2,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  // transportar();
   detectarColor();
  

}


/*
        FLUJO DEL PROGRAMA
Verificar si el botón de la banda es presionado para mandar a la banda a moverse.
OJO: AUN NO SE SABE COMO O QUE SE DEBE DE CUMPLIR PARA PARAR DE TRANSPORTAR PRODUCTOS.
  Dentro de la ejecución de la banda se deberá:
    - Mostrar mensaje de contador de productos que se actualiza cada vez que 
    pasa un producto. Cuando termine de pasar productos debe de quedar durante
    60 segundos: 
      "G12 - Total Productos - # Productos
                  :)"
    - Al mismo tiempo de lo anterior los sensores deberán de estar verificando
    si esta pasando un producto y que tipo de producto es. Si se detecta un
    producto se deberá de verificar lo siguiente:
      _ Color
      _ Tamaño
    Cuando se detecte se deberá de mandar a mover el motor de grados (servo motor)
    Los angulos los defino a continuación en base a mi diseño de banda:
      _ Recipiente 1: 90
      _ Recipiente 2: 120
      _ Recipiente 3: 45
    - Cuando termine de transportar y pasen los 60 segundos del mensaje anterior
    mostrar lo siguiente por cada recipiente cada 60 segundos:
      "¿: G12 - Recipiente X - Y Productos $&"
  Antes de iniciar ejecucion de la banda se debe de mandar a imprimir lo siguiente:
    "¡G12 - SECCION A! - PRACTICA2"
*/
