/*
  AUTEUR: Jan Huijghebaert
  BESCHRIJVING: Met deze code kunnen we de PING))) ultrasonic sensor aansturen.
*/

// Communicatiepin voor de sensor
const int dataPin = 7;

void setup() {
  // Seriële communicatie opzetten
  Serial.begin(9600);
}

void loop()  {
  // Variabelen aanmaken
  long tijdsduur;
  long cm;

  // Om de PING))) sensor te triggeren moeten we een hoge puls van 2 of meer microseconden uitsturen
  pinMode(dataPin, OUTPUT);        // dataPin als output instellen
  digitalWrite(dataPin, LOW);      // verzekeren dat de pin laag staat (voor stabiele activering)
  delayMicroseconds(2);            // wacht 2 microseconden
  digitalWrite(dataPin, HIGH);     // pin hoog zetten om de meting te activeren
  delayMicroseconds(5);            // wacht 5 microseconden
  digitalWrite(dataPin, LOW);      // pin terug laag zetten

  // Via dezelfde datapin gaan we een hoog signaal binnen krijgen en 
  // afhankelijk van hoe lang dit signaal is, kunnen we de afstand tot een object berekenen
  pinMode(dataPin, INPUT);
  tijdsduur = pulseIn(dataPin, HIGH);

  // Omzetten van gemeten tijd naar het aantal centimeters (zie procedure onderaan)
  cm = microsecNaarCentimeters(tijdsduur);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);  // We willen elke 0.1 seconde een afstandsmeting doen
}

long microsecNaarCentimeters(long microseconden)  {
  // Snelheid van geluid is 340,29 m/s of omgerekend 29 microseconden per centimeter
  // Omdat het signaal heen en terug moet komen delen we het geheel door 2
  return microseconden / 29 / 2;
}

