#include <Servo.h> // een bibliotheek om een servo te gebruiken
#include <LiquidCrystal.h> // nog een bibliotheek om een LCD schermpje te gebruiken
#include <Keypad.h> // en dan nog de laatste bibliotheek om een keypad te gebruiken



float boogtangens(float tangent){ // de functie "boogtangens" definiëren
    float tanteken, hoek; // 2 variablen "tanteken en hoek" die in de functie zitten
    tanteken=1; // de functie "tansign" een waarde geven

    if(tangent<0) {
        tanteken=-1;
        tangent*=-1;
    }  
    if(tangent<=1)
        hoek = tanteken*((tangent/(1+ 0.28*tangent*tangent))*57.29);
    else
        hoek = tanteken*(90-((tangent/(tangent*tangent+0.28))*57.29));
       
    return hoek;
}

const byte ROWS = 4; //vier rijen
const byte COLS = 3; //drie kolommen
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {31, 33, 35, 37}; //de pinnen van de rijen van het keypad definen
byte colPins[COLS] = {39,41,43}; //de pinnen van de kolommen van het keypad definen
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // keypad definen

int Contrast=75; // contrast voor het lcd scherm definen
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // pinnen voor het lcd scherm definen
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // lcd scherm definen

int TIP120pin = 8; //for this project, I pick Arduino's PMW pin 11
  int val = 0;
  int lcdin= 0;
  int button = 12;

Servo myservo; // servo definen
int pos = 0; // positie definen van de servo

float Xinputwaarde = 0; // alle variabelen definen
float Yinputwaarde = 0;
float Xwaarde = 0;
float Ywaarde = 0;
long Xtotaal= 0;
long Ytotaal= 0;
double hoek1 = 0;
double hoek2 = 0;
long afstandD = 0;


float zijdehokjes = 20; // zijden van de vierkante hokjes
float afstandwerper = 100; // afstand van de ballen werper tot het rooster

void setup ()
{

 pinMode(TIP120pin, OUTPUT); // Set pin for output to control TIP120 Base pin
 pinMode(button, INPUT);
  Serial.begin (9600); // de seriële monitor opstarten
  analogWrite(6,Contrast); // contrast op het lcd scherm instellen
  lcd.begin(16, 2); // het lcd scherm opstarten
  myservo.attach(7); //de servo moter koppelen aan PWM-pin 7

  lcd.clear(); // zorgen dat het lcd scherm leeg is
  lcd.print("Voorbereiden..."); // voorbereiden afbeelden op het lcd scherm
  myservo.write(0);  // de servo moter op de beginpositie zetten
  delay(1000); // 1 seconden wachten

}
void loop (){
  


lcd.clear();   // zorgen dat het lcd scherm leeg is 
lcd.setCursor(0, 0);  // de cursor van het lcd scherm op de beginpositie zetten
lcd.print("Welkom terug!!!"); // welkom terug op het scherm afbeelden
delay(1000); // een seconden wachten

// X-Coordinaat

lcd.clear(); // het lcd clearen
lcd.print("X-coordinaat:"); // "X-coordinaat:" op het scherm afbeelden
lcd.setCursor(0, 1); // de cursor van het lcd een rij lager zetten

Xtotaal= 0; //zorgen dat deze waarde 0 is
for (int i = 0; i <= 3000; i++) { //de persoon moet 3000 knopjes indrukken voordat de loop gedaan is...
  char keyInputX = 0; //de variabele op 0 zetten
  while (keyInputX == 0){
    keyInputX = keypad.getKey();  //wachten tot er een knop wordt ingedrukt
  }
  if(keyInputX == '#'){ //als de # knop wordt ingedrukt breekt hij de loop en gaat hij door naar het volgende deel van de code
    break;
  }
  if(keyInputX == '*'){ //als de * knop wordt ingedrukt keert hij terug naar het begin
    return;
  }
  Serial.println(keyInputX);
  lcd.setCursor(i, 1); // de cursor van het lcd voor elke knop dat ingedrukt wordt, eentje opschuiven
  lcd.print(keyInputX); //de knop die ingedrukt wordt weergeven op het scherm
  Xtotaal = 10*Xtotaal + keyInputX - 48 ; //we berekenen de totale waarde van X door de voormalige waarde te vermenigvulgdigen maal 10 en op te tellen bij de knop die wordt ingedrukt (min 48 om een char variabele om te zetten naar een long variabele)
  Serial.println(Xtotaal); //de totale waarde van X weergeven op het lcd scherm
  keyInputX = 0; //we zetten de waarde van de knop weer op 0
  delay(10); // een kleine delay is altijd aangeraden in een loop
}

if (Xtotaal > 10 || Xtotaal < 1){ // als de waarde groter is dan 10 of kleiner is dan 1 dan...
    lcd.clear(); // het lcd scherm leegmaken
    lcd.setCursor(0, 0); //cursor van het lcd scherm op beginpositie zetten
    lcd.print("Ongeldige waarde"); //ongeldige waarde weergeven op het scherm
    delay(2000); //2 seconden wachten
    return; // terugkeren naar het begin van de code
}
  lcd.setCursor(14, 0); // de cursor van het lcd scherm verzetten
  lcd.print(Xtotaal); // het x-coordinaat op het lcd scherm weergeven

  Xinputwaarde = -5.50 + Xtotaal*1.00; //de Xinputwaarde berekenen (coordinaat om mee te rekenen)

  Serial.println(Xinputwaarde); //deze waarde ook weergeven op de seriele monitor
  lcd.setCursor(0, 1); //de cursor een lijntje lager zetten
  lcd.print(Xinputwaarde); //deze waarde ook weergeven op het lcd scherm

  delay(3000); // 3 seconden wachten

// Y-Coordinaat
  
lcd.clear(); // het lcd clearen
lcd.print("Y-coordinaat:"); // "Y-coordinaat:" op het scherm afbeelden
lcd.setCursor(0, 1); // de cursor van het lcd een rij lager zetten

Ytotaal= 0; //zorgen dat deze waarde 0 is
for (int i = 0; i <= 3000; i++) { //de persoon moet 3000 knopjes indrukken voordat de loop gedaan is...
  char keyInputY = 0; //de variabele op 0 zetten
  while (keyInputY == 0){
    keyInputY = keypad.getKey();  //wachten tot er een knop wordt ingedrukt
  }
  if(keyInputY == '#'){ //als de # knop wordt ingedrukt breekt hij de loop en gaat hij door naar het volgende deel van de code
    break;
  }
  if(keyInputY == '*'){ //als de * knop wordt ingedrukt keert hij terug naar het begin
    return;
  }
  Serial.println(keyInputY);
  lcd.setCursor(i, 1); // de cursor van het lcd voor elke knop dat ingedrukt wordt, eentje opschuiven
  lcd.print(keyInputY); //de knop die ingedrukt wordt weergeven op het scherm
  Ytotaal = 10*Ytotaal + keyInputY - 48 ; //we berekenen de totale waarde van Y door de voormalige waarde te vermenigvulgdigen maal 10 en op te tellen bij de knop die wordt ingedrukt (min 48 om een char variabele om te zetten naar een long variabele)
  Serial.println(Ytotaal); //de totale waarde van Y weergeven op het lcd scherm
  keyInputY = 0; //we zetten de waarde van de knop weer op 0
  delay(10); // een kleine delay is altijd aangeraden in een loop
}

if (Ytotaal > 10 || Ytotaal < 1){ // als de waarde groter is dan 10 of kleiner is dan 1 dan...
    lcd.clear(); // het lcd scherm leegmaken
    lcd.setCursor(0, 0); //cursor van het lcd scherm op beginpositie zetten
    lcd.print("Ongeldige waarde"); //ongeldige waarde weergeven op het scherm
    delay(2000); //2 seconden wachten
    return; // terugkeren naar het begin van de code
}
  lcd.setCursor(14, 0); // de cursor van het lcd scherm verzetten
  lcd.print(Ytotaal); // het x-coordinaat op het lcd scherm weergeven

  Yinputwaarde = -0.50+Ytotaal*1.00; //de Yinputwaarde berekenen (coordinaat om mee te rekenen)

  Serial.println(Yinputwaarde); //deze waarde ook weergeven op de seriele monitor
  lcd.setCursor(0, 1); //de cursor een lijntje lager zetten
  lcd.print(Yinputwaarde); //deze waarde ook weergeven op het lcd scherm


// hoek berekenen

  delay(3000); // 3 seconden wachten

  lcd.clear();
  lcd.setCursor(0, 0);   // cursor van het lcd op beginpositie zetten
  lcd.print("X-coordinaat:"); //  "X-coordinaat:" op het lcd zetten
  lcd.setCursor(0, 1);    // cursor van het lcd op de volgende lijn zetten
  lcd.print("Y-coordinaat:"); //  "Y-coordinaat:" op het lcd zetten
  lcd.setCursor(14, 0); // cursor van lcd verzetten
  lcd.print(Xtotaal);    // het X coordinaat die ingedrukt werd weergeven op het lcd
  lcd.setCursor(14, 1);  // cursor van lcd verzetten
  lcd.print(Ytotaal);  // het Y coordinaat weergeven op het lcd
  delay(3000);
  Xwaarde = Xinputwaarde*zijdehokjes;  // X inputwaarde vermenigvuldigen met de lengte van de zijden van de hokjes
  Ywaarde = (Yinputwaarde*zijdehokjes) + afstandwerper; // Y inputwaarde vermenigvuldigen met de lengte van de zijden van de hokjes en optellen bij de afstand tussen het rooster en de ballenwerper
  Serial.println(Xwaarde); //de totale Xwaarde printen op  het lcd
  Serial.println(Ywaarde); //de totale Ywaarde printen op  het lcd

  hoek1 = boogtangens(Ywaarde/Xwaarde); //de hoek bereken: boogtangens van de  totale Ywaarde gedeeld door de totale Xwaarde
  Serial.println(hoek1); // de hoek weergeven op de seriële monitor
  if (hoek1 < 0){ // als de hoek negatief is dan berekent hij de hoek vanaf de beginpositie van de servo motor door gewoon de uiteindelijke hoek gelijk te stellen aan de eerst berekende hoek maal -1
       hoek2 = hoek1 * - 1.00; 
      Serial.println(hoek2);
    }
  if (hoek1 > 0){ // als de hoek positief is dan berekent hij ook de hoek vanaf de beginpositie van de servo motor door 90 op te tellen bij de boogtangens van de Ywaarde gedeeld door de Xwaarde
       hoek2 = 90+(boogtangens(Xwaarde/Ywaarde));
      Serial.println(hoek2);
    }
  lcd.clear(); // het lcd scherm leeg maken
  lcd.print("Benodigde hoek:"); // "Benodigde hoek:" weergeven op het lcd scherm
  lcd.setCursor(0,1); // de cursor een lijntje lager zetten
  lcd.print(hoek2 - myservo.read()); // de hoek dat de servo moet draaien op het lcd scherm weergeven
  delay(2000); //wacht 2 seconden

if(hoek2 >= myservo.read()){ //kijkt naar welke kant de servo moet draaien
  for (pos = myservo.read(); pos <= hoek2; pos += 1) { // gaat van zijn positie tot de grootte van de uiteindelijke hoek
    myservo.write(pos);              //laat de motor naar de juiste hoek bepaalt door variabele 'pos' bewegen
    delay(15);                       // snelheid : 15ms/graad
  }
} else {
   for (pos = myservo.read(); pos >= hoek2; pos -= 1) { // gaat van 0 graden tot de grootte van de uiteindelijke hoek
   myservo.write(pos);              //laat de motor naar de juiste hoek bepaalt door variabele 'pos' bewegen
   delay(15);                       // snelheid : 15ms/graad
   }
}


// afstand berekenen

  afstandD = sqrt(sq(Xwaarde) + sq(Ywaarde));
  lcd.clear(); // het lcd scherm leeg maken
  lcd.print("Afstand:"); // "Benodigde afstand:" weergeven op het lcd scherm
  lcd.setCursor(0,1); // de cursor een lijntje lager zetten
  lcd.print(afstandD); // de uiteindelijke afstand op het lcd scherm weergeven
  lcd.setCursor(5,1); // de cursor van het lcd scherm verzetten
  lcd.print("cm"); // "cm" op het lcd scherm weergeven+
  delay(3000); // wacht 3 seconden
//balletje schieten
int inputbutton = analogRead(button);

while(inputbutton = HIGH){
val = analogRead(A2);
lcdin = map(val,0,1024,0,255);
lcd.clear();
lcd.println(lcdin);
analogWrite(TIP120pin, lcdin); // By changing values from 0 to 255
delay(100);
}
delay(5000); // wacht 5 seconden

}
