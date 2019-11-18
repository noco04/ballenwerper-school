#include <LiquidCrystal.h> // nog een bibliotheek om een LCD schermpje te gebruiken
int Contrast=75; // contrast voor het lcd scherm definen
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // pinnen voor het lcd scherm definen
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // lcd scherm definen
int TIP120pin = 8; //for this project, I pick Arduino's PMW pin 11
  int val = 0;
  int lcdin= 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin (9600); // de seriële monitor opstarten
  analogWrite(6,Contrast); // contrast op het lcd scherm instellen
  lcd.begin(16, 2); // het lcd scherm opstarten
pinMode(TIP120pin, OUTPUT); // Set pin for output to control TIP120 Base pin

}

void loop() {
  // put your main code here, to run repeatedly:
val = analogRead(A2);
lcdin = map(val,0,1024,0,255);
lcd.clear();
lcd.println(lcdin);
analogWrite(TIP120pin, lcdin); // By changing values from 0 to 255
delay(100);
}
