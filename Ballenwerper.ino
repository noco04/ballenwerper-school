

//libraries
#include <Servo.h>
#include <AccelStepper.h>
#include <LiquidCrystal.h>
#include <Keypad.h>



float boogtangens(float tangent){
    //Return atan in degrees
    //returns value between -90 and +90
    float tansign, angle;
    tansign=1;

    if(tangent<0) {
        tansign=-1;
        tangent*=-1;
    }
    if(tangent<=1)
        angle = tansign*((tangent/(1+ 0.28*tangent*tangent))*57.29);
    else
        angle = tansign*(90-((tangent/(tangent*tangent+0.28))*57.29));
       
    return angle;
}



//defining
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

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {39,41,43}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int Contrast=75;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


Servo myservo;
int pos = 0;

float Xinputwaarde = 0;
float Yinputwaarde = 0;
float Xwaarde = 0;
float Ywaarde = 0;
double hoek2 = 0;

float zijdehokjes = 20;
float afstandwerper = 100;

void setup ()
{
  stepper.setMaxSpeed(1000.0);      // stel de maximale motorsnelheid in
  stepper.setAcceleration(1000.0);   // stel de acceleratie in
  stepper.setSpeed(1000.0);            // stel de huidige snelheid in
  
  pinMode (KEYin, INPUT);
  Serial.begin (9600); 
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  myservo.attach(7);
  

}
void loop ()

{
lcd.clear();
lcd.print("Voorbereiden...");
myservo.write(0);
delay(1000);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Welkom terug!!!");
delay(1000);
lcd.clear();
lcd.print("X-coordinaat:");
char key = keypad.getKey();
while (!key){
  key = keypad.getKey();
  }
  if (key == '*' || key == '#'){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ongeldige waarde");
    delay(2000);
    return;
    }
  lcd.setCursor(14, 0);
  lcd.print(key);
  
  if (key == '1'){Xinputwaarde = -4.50;};
  if (key == '2'){Xinputwaarde = -3.50;};
  if (key == '3'){Xinputwaarde = -2.50;};
  if (key == '4'){Xinputwaarde = -1.50;};
  if (key == '5'){Xinputwaarde = -0.5;};
  if (key == '6'){Xinputwaarde = 0.50;};
  if (key == '7'){Xinputwaarde = 1.50;};
  if (key == '8'){Xinputwaarde = 2.50;};
  if (key == '9'){Xinputwaarde = 3.50;};
  if (key == '0'){Xinputwaarde = 4.50;};
  Serial.println(Xinputwaarde);
  lcd.setCursor(0, 1);
  lcd.print(Xinputwaarde);

  delay(3000);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Y-coordinaat:");
char key2 = keypad.getKey();
while (!key2){
  key2 = keypad.getKey();
  }
    if (key2 == '*' || key2 == '#'){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ongeldige waarde");
    delay(2000);
    return;
    }
  lcd.setCursor(14, 0);
  lcd.print(key2);

  if (key2 == '1'){Yinputwaarde = 0.50;};
  if (key2 == '2'){Yinputwaarde = 1.50;};
  if (key2 == '3'){Yinputwaarde = 2.50;};
  if (key2 == '4'){Yinputwaarde = 3.50;};
  if (key2 == '5'){Yinputwaarde = 4.50;};
  if (key2 == '6'){Yinputwaarde = 5.50;};
  if (key2 == '7'){Yinputwaarde = 6.50;};
  if (key2 == '8'){Yinputwaarde = 7.50;};
  if (key2 == '9'){Yinputwaarde = 8.50;};
  if (key2 == '0'){Yinputwaarde = 9.50;};
  Serial.println(Yinputwaarde);
  lcd.setCursor(0, 1);
  lcd.print(Yinputwaarde);
  


  delay(3000);

  lcd.setCursor(0, 0);  
  lcd.print("X-coordinaat:");
  lcd.setCursor(0, 1); 
  lcd.print("Y-coordinaat:");
  lcd.setCursor(14, 0);
  lcd.print(key);  
  lcd.setCursor(14, 1);  
  lcd.print(key2);  
  delay(3000);
  Xwaarde = Xinputwaarde*zijdehokjes;
  Ywaarde = (Yinputwaarde*zijdehokjes) + afstandwerper;
  Serial.println(Xwaarde);
  Serial.println(Ywaarde);

  double hoek1 = boogtangens(Ywaarde/Xwaarde);
  Serial.println(hoek1);
  if (hoek1 < 0){
       hoek2 = 90-(90+hoek1);
      Serial.println(hoek2);
    }
  if (hoek1 > 0){
       hoek2 = 90+(boogtangens(Xwaarde/Ywaarde));
      Serial.println(hoek2);
    }
  for (pos = 0; pos <= hoek2; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

delay(5000);

}

float degToSteps(float deg) {
  return (stepsPerRevolution / degreePerRevolution) * deg;
}
