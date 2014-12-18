/*
  AUTEUR: Jan Huijghebaert
  BESCHRIJVING: Met deze code kunnen we de 3 PING))) ultrasonic sensoren
                vooraan op de Stingray aansturen.
*/

// Communicatiepinnen voor de sensoren (digitalPin)
const int dataPin_l = 2;
const int dataPin_m = 4;
const int dataPin_r = 7;

void setup()  {
  // Seriële verbinding opzetten
  Serial.begin(9600);
}

void loop()  {
  // Variabelen aanmaken
  long tijdsduur_l;
  long tijdsduur_m;
  long tijdsduur_r;
  long cm_l;
  long cm_m;
  long cm_r;
  
  // Sensoren triggeren
  // -- Sensor links meting
  pinMode(dataPin_l, OUTPUT);
  digitalWrite(dataPin_l, LOW);
  delayMicroseconds(2);
  digitalWrite(dataPin_l, HIGH);
  delayMicroseconds(5);
  digitalWrite(dataPin_l, LOW);
  pinMode(dataPin_l, INPUT);
  tijdsduur_l = pulseIn(dataPin_l, HIGH);
  // -- Sensor midden meting
  pinMode(dataPin_m, OUTPUT);
  digitalWrite(dataPin_m, LOW);
  delayMicroseconds(2);
  digitalWrite(dataPin_m, HIGH);
  delayMicroseconds(5);
  digitalWrite(dataPin_m, LOW);
  pinMode(dataPin_m, INPUT);
  tijdsduur_m = pulseIn(dataPin_m, HIGH);
  // -- Sensor rechts meting
  pinMode(dataPin_r, OUTPUT);
  digitalWrite(dataPin_r, LOW);
  delayMicroseconds(2);
  digitalWrite(dataPin_r, HIGH);
  delayMicroseconds(5);
  digitalWrite(dataPin_r, LOW);
  pinMode(dataPin_r, INPUT);
  tijdsduur_r = pulseIn(dataPin_r, HIGH);
  
  // Omzetten naar centimeters
  cm_l = microsecNaarCentimeters(tijdsduur_l);
  cm_m = microsecNaarCentimeters(tijdsduur_m);
  cm_r = microsecNaarCentimeters(tijdsduur_r);
  
  Serial.print(cm_l);
  Serial.print("cm   ");
  Serial.print(cm_m);
  Serial.print("cm   ");
  Serial.print(cm_r);
  Serial.print("cm");
  Serial.println();
  
  delay(50);
}

long microsecNaarCentimeters(long microseconden)  {
  // Snelheid van geluid is 340,29 m/s of omgerekend 29 microseconden per centimeter
  // Omdat het signaal heen en terug moet komen delen we het geheel door 2
  return microseconden / 29 / 2;
}
