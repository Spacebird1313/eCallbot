/*
  AUTEUR: Jan Huijghebaert
  BESCHRIJVING: Met deze code heb ik de eerste versie van de GUI getest
*/

int led = 13;
int flag = 0;
char input;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0)  {
    input = Serial.read();
    flag = 1;
  }
  if(input == 'a')  {
    digitalWrite(led, HIGH);
    if(flag == 1)  {
      Serial.println("Led aan!");
      flag = 0;
    }
  } else if(input == 'u')  {
    digitalWrite(led, LOW);
    if(flag == 1)  {
      Serial.println("Led uit!");
      flag = 0;
    }
  } else {
  }
}
