#include <LiquidCrystal_I2C.h>
#include<Wire.h>
#include<string.h>

LiquidCrystal_I2C lcd(0x27,16,2); //0x20 o 0x27
// ¿  ¡

int totProductos = 0;
int totRecipientes = 0;


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

void setup() {
  lcd.init();
  lcd.backlight();          // Activar luz de fondo 
  lcd.clear();              // Borrar LCD
  lcd.createChar(0, pregunta);
  lcd.createChar(1, exclamacion);
  lcd.home();

}

void loop() { 
  
  msg1();
  delay(1000);
  msg2 ();
  delay(1000);
}

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
  totProductos++;
  }
