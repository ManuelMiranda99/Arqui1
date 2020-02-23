/*
  ------------------------------Librerias a usar---------------------------------
*/
#include <Servo.h>                // Libreria de Servo (Grados) 

#include <LiquidCrystal_I2C.h>
#include<Wire.h>
#include<string.h>
LiquidCrystal_I2C lcd(0x27,16,2); //0x20 o 0x27

/*
  ------------------------------Fin de librerias---------------------------------
*/

/*
  ------------------------------Pines usados-------------------------------------
*/
// Servo

#define SERVOPIN 9                 // Pin del servo
//#define REC1 0                   // Constante de recipiente 1
//#define REC2 90                  // Constante de recipiente 2
//#define REC3 180                   // Constante de recipiente 3  

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
#define S1 4  
#define S2 5
#define S3 6
#define S4 7

#define SOut 8
//Motor de la banda
#define INICIO 48
#define MOTOR 50

/*
  ------------------------------Fin de pines usados-------------------------------
*/

/*
  ------------------------------Variables a utilizar------------------------------
*/
// Lugar para meter variables nosotros \>:V/
//int productosTotales = 0,
int productosR1 = 0, productosR2 = 0, productosR3 = 0;

int totProductos = 0;
//int totRecipientes = 0; 
int distanciaRecorrida=100;
int rojo=0;
int verde=0;
int azul=0;

// Lugar de objetos y variables necesarias para los motores \>:V/
Servo servo;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
/*
  ------------------------------Fin de variables----------------------------------
*/
/*
  ------------------------------Arreglos para LCD---------------------------------
*/
byte abrirEx[] = {    // !
  0b00000000,
  0b00001100,
  0b00001100,
  0b00001100,
  0b00001100,
  0b00000000,
  0b00001100,
  0b00001100
};

byte pregunta[] = { // ¿
  B00000000,
  B00000100,
  B00000000,
  B00000100,
  B00001000,
  B00010000,
  B00001001,
  B00000110
};

byte exclamacion[] = {   // ¡
  0b00000100,
  0b00000100,
  0b00000000,
  0b00000100,
  0b00000100,
  0b00000100,
  0b00000100,
  0b00000000
};


boolean activo=false;

int tamanio;
int color;
int grados;


// Lugar de objetos y variables necesarias para los motores \>:V/
Servo servo;
//LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
/*
  ------------------------------Fin de variables----------------------------------
*/

void transportar(){
 

    
}

//Metodo para mostrar mensajes
void msg1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(1);
  lcd.print("G12- SECCION A!");
  lcd.setCursor(0,1);
  lcd.print("   - PRACTICA2");
  }

void msg2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("G12-TOTAL");
  lcd.setCursor(0,1);
  lcd.print("PRODUCTOS-");
  lcd.print(totProductos);
  lcd.print(" :)");
 
  }

  //¿: G12 - Recipiente X - Y Productos $&
void msg3(int _r, int _c){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(0);
  lcd.print(": G12 - Recipiente");
  lcd.print(_r);
  lcd.setCursor(0,1);
  lcd.print(_c);
  lcd.print(" Productos $&");
  delay(60000);
}

//Metodo para calcular tamaño
void detectarDistancia(){
   digitalWrite(TRIGGERUS,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERUS,LOW);
  int tiempo=pulseIn(ECHO,HIGH);
  distanciaRecorrida=tiempo/59;

  if(distanciaRecorrida<9){
    if(distanciaRecorrida>7){
      tamanio=0;
    }
    else if(distanciaRecorrida>5){
      tamanio=1;
      }
    else if(distanciaRecorrida>3){
      tamanio=2;
      }
  }
  else{
    tamanio=3;
    }

  Serial.print("Distancia: ");
  Serial.print(distanciaRecorrida);
  Serial.print("cm");
  Serial.println();
 // delay(10);
  }

// Metodo a llamar para mover servomotor cierta cantidad de grados
void moverServo(int _grados){
     Serial.println("ENTROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");  

  servo.write(_grados);
}
//Metodo a llamar para sensor de color
void detectarColor(){
  calcularColor();
  Serial.print("   ");
  Serial.print(rojo,DEC);
  Serial.print("   ");
  Serial.print(verde,DEC);
  Serial.print("   ");
  Serial.print(azul,DEC);

  if (rojo < azul && verde > azul && rojo < 35) 
  {  
   Serial.println("   Rojo");  
   color=1; 
  }   
  else if (azul < rojo && azul < verde && verde < rojo)  
  {  
   Serial.println("   Azul");  
   color=0;      
  }  

  else if (rojo > verde && azul > verde )  
  {  
   Serial.println("   Verde");     
   color=2;  
  }  
  else{
  Serial.println("  ");  
  color=3;
  }
//  delay(1000);     
  }  
    
  
  
//Metodo que devuelve el tipo de recipiente
void calculoGrados(int a, int b){
  //---Posibles valores------------>0,45,135
  if(a==0&&b==0){
    grados=REC1;
    productosR1++;
    }
  else if(a==1&&b==0){
    grados=REC2;
        productosR2++;

    }
    else if(a==2&&b==0){
          grados=REC3;
                  productosR3++;

      }
      else if(a==0&&b==1){
            grados=REC3;
                              productosR3++;

        }
        else if(a==1&&b==1){
              grados=REC1;
                  productosR1++;

          }
          else if(a==2&&b==1){
                grados=REC2;
                        productosR2++;

            }
            else if(a==0&&b==2){
                  grados=REC2;
                          productosR2++;

              }
              else if(a==1&&b==2){
                    grados=REC3;
                                      productosR3++;

                }
                else if(a==2&&b==2){
                      grados=REC1;
                          productosR1++;

                  }
               
    totProductos++;
  }
void calcularColor(){
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
  servo.attach(9);
  // Mover servo a posición de Recipiente 1

  
  moverServo(0);

  // Setup de LCD
  lcd.init();
  lcd.backlight();          // Activar luz de fondo 
  lcd.clear();              // Borrar LCD
  lcd.createChar(0, pregunta);
  lcd.createChar(1, exclamacion);
  lcd.home();
  
 // lcd.begin(16, 2);

 //Setup del sensor de color
 pinMode(S1,OUTPUT);
 pinMode(S2,OUTPUT);
 pinMode(S3,OUTPUT);
 pinMode(S4,OUTPUT);
 pinMode(SOut,INPUT);

 digitalWrite(S1,HIGH);
 digitalWrite(S2,HIGH);
 //Setup del motor de la banda
 pinMode(MOTOR,OUTPUT);
 pinMode(INICIO,INPUT);
 digitalWrite(INICIO,LOW);
 digitalWrite(MOTOR,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  
   if(digitalRead(INICIO)==HIGH){
    Serial.print("-------------------------------------------- \n");
    Serial.print("-------------------------------------------- \n");
    Serial.print("-------------------------------------------- \n");
    
    activo=!activo;
    }

  if(activo){
      msg2 ();
    digitalWrite(MOTOR,HIGH);
    detectarDistancia();

    if(tamanio!=3){
       detectarColor();
       calculoGrados(color,tamanio);
       delay(3000);
       moverServo(grados);
    }
  }else{
    msg1();
    digitalWrite(MOTOR,LOW);
  }
     delay(100);
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
