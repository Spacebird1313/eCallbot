/*
  AUTEUR: Jan Huijghebaert
  BESCHRIJVING: Testen van de Bluetooth-module
*/
 
int led_green_1 = 30;
int led_green_2 = 31;
int led_yellow_1 = 32;
int led_yellow_2 = 33;
int led_orange_1 = 34;
int led_orange_2 = 35;
char state;
int printtext = 0;

void setup() {
  pinMode(led_green_1, OUTPUT);
  pinMode(led_green_2, OUTPUT);
  pinMode(led_yellow_1, OUTPUT);
  pinMode(led_yellow_2, OUTPUT);
  pinMode(led_orange_1, OUTPUT);
  pinMode(led_orange_2, OUTPUT);
  digitalWrite(led_green_1, HIGH);
  digitalWrite(led_green_2, LOW);
  digitalWrite(led_yellow_1, HIGH);
  digitalWrite(led_yellow_2, LOW);
  digitalWrite(led_orange_1, HIGH);
  digitalWrite(led_orange_2, LOW);
  delay(5000);
  clearLeds();
  Serial1.begin(9600);
}
 
void loop() {
    if(Serial1.available() > 0)  {     
      state = Serial1.read();   
      printtext = 1;
    }
    
    // GREEN
    if(state == 'g')  {
      clearLeds();
      digitalWrite(led_green_1, HIGH);
      digitalWrite(led_green_2, HIGH);
      if(printtext == 1)  {
        Serial1.println("Groene leds aan!");
        printtext = 0;
      }
    // YELLOW
    } else if(state == 'y')  {
      clearLeds();
      digitalWrite(led_yellow_1, HIGH);
      digitalWrite(led_yellow_2, HIGH);
      if(printtext == 1)  {
        Serial1.println("Gele leds aan!");
        printtext = 0;
      }
    } else if(state == 'o')  {
      clearLeds();
      digitalWrite(led_orange_1, HIGH);
      digitalWrite(led_orange_2, HIGH);
      if(printtext == 1)  {
        Serial1.println("Oranje leds aan!");
        printtext = 0;
      }
    } else {
      clearLeds();
      if(printtext == 1)  {
        Serial1.println("Leds uit!");
        printtext = 0;
      }
    }
}

void clearLeds()  {
  digitalWrite(led_green_1, LOW);
  digitalWrite(led_green_2, LOW);
  digitalWrite(led_yellow_1, LOW);
  digitalWrite(led_yellow_2, LOW);
  digitalWrite(led_orange_1, LOW);
  digitalWrite(led_orange_2, LOW);
}
