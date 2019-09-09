#include <AccelStepper.h>
#include <LiquidCrystal.h>

#define motorPin1  50                // IN1 pin op de ULN2003A driver
#define motorPin2  51               // IN2 pin op de ULN2003A driver
#define motorPin3  52               // IN3 pin op de ULN2003A driver
#define motorPin4  53              // IN4 pin op de ULN2003A driver
int stepsPerRevolution = 64;        // stappen per omwenteling
float degreePerRevolution = 5.625;  // graden per omwenteling
AccelStepper stepper(AccelStepper::HALF4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

int Xin= A1; // X Input Pin
int Yin = A2; // Y Input Pin
int KEYin = 13; // Push Button

int Contrast=75;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup ()
{
  stepper.setMaxSpeed(1000.0);      // stel de maximale motorsnelheid in
  stepper.setAcceleration(1000.0);   // stel de acceleratie in
  stepper.setSpeed(1000.0);            // stel de huidige snelheid in
  
  pinMode (KEYin, INPUT);
  Serial.begin (9600); 
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
}
void loop ()

{
  int xVal, yVal, buttonVal;
  xVal = analogRead (Xin);
  yVal = analogRead (Yin);
  buttonVal = digitalRead (KEYin);
  
  Serial.print("X = ");
  Serial.println (xVal, DEC);
  
  Serial.print ("Y = ");
  Serial.println (yVal, DEC);
  
  Serial.print("Button is ");
  if (buttonVal == HIGH){
    Serial.println ("not pressed");
  }
  else{
    Serial.println ("PRESSED");
  }
if (yVal > 750) {
 Serial.println("Vooruit");
 
  lcd.setCursor(0, 0);  
  lcd.print("Vooruit");
    while (yVal > 750) {
  stepper.move (-20);
  stepper.run();
  xVal = analogRead (Xin);
  yVal = analogRead (Yin);
  
}
} 
if (yVal < 250) {
  Serial.println("Achteruit");
  lcd.setCursor(0, 0);
  lcd.print("Achteruit");
  
  while (yVal < 250) {
  stepper.move (20);
  stepper.run();
  xVal = analogRead (Xin);
  yVal = analogRead (Yin);
  
}


}
if ((yVal >=250) && (yVal <= 750)){
Serial.println("Stoppen");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.clear();
  
}
delay (100);
}

float degToSteps(float deg) {
  return (stepsPerRevolution / degreePerRevolution) * deg;
}
