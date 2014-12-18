/*
  AUTEUR: Jan Huijghebaert
  BESCHRIJVING: Code voor het gebruiken van de positie controllers
*/

void setup() {
  extern HardwareSerial Serial3;
  Serial3.begin(19200);  // Naar encoder
  Serial.begin(19200);   // Om informatie te kunnen zien in terminal

  # define QPOS         0x08            // Positie opvragen
  # define QSPD         0x10            // Snelheid opvragen
  # define CHFA         0x18            // Aankomst checken
  # define TRVL         0x20            // Verplaats # posities van encoderwiel
  # define CLRP         0x28            // Positie resetten
  # define SREV         0x30            // Instellen oriëntatie draairichting
  # define STXD         0x38            // Instellen vertraging Tx encoder
  # define SMAX         0x40            // Instellen maximum snelheid
  # define SSRR         0x48            // Instellen snelheid (ramp rate)
  # define Wiel_Links   0x01            // Instellen adres van het linkse wiel
  # define Wiel_Rechts  0x02            // Instellen adres van het rechtse wiel
  # define Wiel_Beide   0x00            // Instellen adres van beide wielen
  
  Serial.println("Draairichting rechtse wiel juist instellen");
  Instellen_Draairichting_Omdraaien(Wiel_Rechts);
  delay(150);
}

void loop()  {
  int aantalmetingen = 100;
  Serial.println("Positie van beide wielen resetten...");
  Positie_Resetten(Wiel_Beide);
  delay(150);
  Serial.println("----- Loop van snelheidsmetingen (5) -----");
  for(int i = 0; i < aantalmetingen; i++)  {
    Serial.print("S: ");
    Serial.print(Conv_Snelheid(Opvragen_Snelheid(Wiel_Links)));
    delay(150);
    Serial.print(" m/s\tP: ");
    Serial.print(Conv_Positie(Opvragen_Positie(Wiel_Links)));
    delay(150);
    Serial.print(" m\tS: ");
    Serial.print(Conv_Snelheid(Opvragen_Snelheid(Wiel_Rechts)));
    delay(150);
    Serial.print(" m/s\tP: ");
    Serial.print(Conv_Positie(Opvragen_Positie(Wiel_Rechts)));
    Serial.println(" m");
    delay(150);
  }
  delay(30000);
}

// Positie opvragen
int Opvragen_Positie(byte Wiel)  {
  int Resultaat; 
  Resultaat = Stuur_Naar_Encoder( QPOS,  Wiel,  0);
  return Resultaat;
}

// Snelheid opvragen
int Opvragen_Snelheid(byte Wiel)  {
  int Resultaat; 
  Resultaat = Stuur_Naar_Encoder( QSPD,  Wiel,  0);
  return Resultaat;
}

// Aankomst checken
// Tolerantie: 0 - 255 (0 = exact, 255 = slordig)
int Checken_Op_Aankomst(byte Wiel, int Tolerantie)  {
  int Resultaat; 
  Resultaat = Stuur_Naar_Encoder( CHFA,  Wiel,  Tolerantie);
  return Resultaat;
}

// Verplaats # posities van encoderwiel
int Verplaats_Aantal_Encoderposities(byte Wiel, int Aantal_Posities)  {
  int Resultaat; 
  Resultaat = Stuur_Naar_Encoder( TRVL,  Wiel,  Aantal_Posities);
  return Resultaat;
}

// Positie resetten
void Positie_Resetten(byte Wiel) {
  int Resultaat;
  Resultaat = Stuur_Naar_Encoder( CLRP,  Wiel,  0);
}

// Draairiching omdraaien
void Instellen_Draairichting_Omdraaien(byte Wiel) {
  int Resultaat;
  Resultaat = Stuur_Naar_Encoder( SREV,  Wiel,  0);
}

// Instellen transmit vertraging encoder
void Instellen_Transmit_Vertraging(byte Vertraging) {
  int Resultaat;
  Resultaat = Stuur_Naar_Encoder( STXD, 0, Vertraging);
}

// Instellen maximum snelheid
// Snelheid is een getal tussen 0 en 65535
void Instellen_Max_Snelheid(byte Wiel, int Snelheid) {
  int Resultaat;
  Resultaat = Stuur_Naar_Encoder( SMAX,  Wiel,  Snelheid);
}

// Instellen snelheid (ramp rate)
// Ramp_Rate is een getal tussen 0 en 65535
void Instellen_Ramp_Rate(byte Wiel, byte Ramp_Rate) {
  int Resultaat;
  Resultaat = Stuur_Naar_Encoder( SSRR,  Wiel,  Ramp_Rate);
}

// Verzenden van data naar de encoder en eventueel informatie terug ontvangen
int Stuur_Naar_Encoder(byte Commando, byte Adres, int Parameter) {
  
  # define DEBUG         0x00  // Zet op 0x00 als deze informatie niet getoond moet worden

  // Variabelen
  int Num_Bytes_Schrijf; 
  int Num_Bytes_Lees;
  int Num_Bytes_Wachtrij;
  byte Output_Buffer[4];
  byte Input_Buffer[4];
  int Teruggezonden_Data;
  
  // Bytes om uit te sturen
  Output_Buffer[0] = 0;
  Output_Buffer[1] = 0;
  Output_Buffer[2] = 0;
  Output_Buffer[3] = 0;
  
  Output_Buffer[0] = Commando + Adres;
  
  Serial3.flush();
  
  // DEBUG PRINTFUNCTIE
  if(DEBUG)  {
    Serial.println("---------- DEBUG ----------");
  }
  
  // Commando's
  if(Commando == QPOS)  {
    Num_Bytes_Schrijf = 1;
    Num_Bytes_Lees = 2;
    if(DEBUG)  {Serial.println("QPOS");}
  } else if(Commando == QSPD)  {
    Num_Bytes_Schrijf = 1;
    Num_Bytes_Lees = 2;
    if(DEBUG)  {Serial.println("QSPD");}
  } else if(Commando == CHFA)  {
    Num_Bytes_Schrijf = 2;
    Num_Bytes_Lees = 1;
    Output_Buffer[1] = byte(Parameter);
    if(DEBUG)  {Serial.println("CHFA");}
  } else if(Commando == TRVL)  {
    Num_Bytes_Schrijf = 3;
    Num_Bytes_Lees = 0;
    Output_Buffer[1] = byte(Parameter / 256);  // Hoge byte
    Output_Buffer[2] = byte(Parameter);        // Lage byte
    if(DEBUG)  {Serial.println("TRVL");}
  } else if(Commando == CLRP)  {
    Num_Bytes_Schrijf = 1;
    Num_Bytes_Lees = 0;
    if(DEBUG)  {Serial.println("CLRP");}
  } else if(Commando == SREV)  {
    Num_Bytes_Schrijf = 1;
    Num_Bytes_Lees = 0;
    if(DEBUG)  {Serial.println("SREV");}
  } else if(Commando == STXD)  {
    Num_Bytes_Schrijf = 2;
    Num_Bytes_Lees = 0;
    Output_Buffer[1] = byte(Parameter);
    if(DEBUG)  {Serial.println("STXD");}
  } else if(Commando == SMAX)  {
    Num_Bytes_Schrijf = 3;
    Num_Bytes_Lees = 0;
    Output_Buffer[1] = byte(Parameter / 256);  // Hoge byte
    Output_Buffer[2] = byte(Parameter);        // Lage byte
    if(DEBUG)  {Serial.println("SMAX");}
  } else if(Commando == SSRR)  {
    Num_Bytes_Schrijf = 2;
    Num_Bytes_Lees = 0;
    Output_Buffer[1] = byte(Parameter);
    if(DEBUG)  {Serial.println("SSRR");}
  }
  
  // DEBUG PRINTFUNCTIE
  if(DEBUG)  {  
    Serial.print("Stuur naar encoder => ");
    Serial.println(Commando, BIN);
    Serial.print("Adres => ");
    Serial.println(Adres, BIN);
    Serial.print("Parameter => ");
    Serial.println(Parameter, DEC);
    Serial.print("Output_Buffer => ");
    for(int i = 0; i < Num_Bytes_Schrijf; i++){
      Serial.print(Output_Buffer[i], HEX);
      Serial.print(", ");
    }
    Serial.print("Aantal verzonden bytes: ");
    Serial.println(Num_Bytes_Schrijf, DEC);
    Serial.print("Aantal te ontvangen bytes: ");
    Serial.println(Num_Bytes_Lees, DEC);
  }

  // Verzenden!
  for (int i=0; i < Num_Bytes_Schrijf; i++) {
     Serial3.write(Output_Buffer[i]);
  }
  
  // Om een stabiele overdracht te hebben nemen we een kleine pauze
  delay(100);
  
  // Aantal wachtend bytes in wachtrij
  // Opgepast! Hierbij zit ook de echo request van de Tx pin
  // Dus de eerste byte die is binnengekomen moet gedropt worden
  Num_Bytes_Wachtrij = Serial3.available();  
  
  // DEBUG PRINTFUNCTIE
  if(DEBUG) {
    Serial.print("Aantal bytes in de wachtrij: ");  
    Serial.println(Num_Bytes_Wachtrij, DEC);
    Serial.print("Input bytes: ");
  }

  // Inlezen van de binnengekomen bytes
  for(int i = 0; i < Num_Bytes_Wachtrij; i++) {
    Input_Buffer[i] = Serial3.read();
    if(DEBUG) {
      Serial.print(Input_Buffer[i],HEX);  
      Serial.print(", ");
    }
  }
  if(DEBUG)  {
    Serial.println("");
  }

  // Resultaten teruggeven
  if(Num_Bytes_Lees == 0)  {
    Teruggezonden_Data = 0;
  } else if(Num_Bytes_Lees == 1)  {
    Teruggezonden_Data = Input_Buffer[Num_Bytes_Wachtrij - 1];
  } else if(Num_Bytes_Lees == 2)  {
    Teruggezonden_Data = (256 * Input_Buffer[Num_Bytes_Wachtrij - 2]) + Input_Buffer[Num_Bytes_Wachtrij - 1];
  }
  
  // DEBUG PRINTFUNCTIE
  if(DEBUG)  {
    Serial.print("Teruggezonden data: ");
    Serial.println(Teruggezonden_Data, DEC);
    Serial.println("-------- DEBUG END --------");
  }
  
  return Teruggezonden_Data;    
}

/*
  INFO VOOR CONVERSIE FUNCTIES
  Diameter wiel = 0,1238 meter dus
  Omtrek wiel = 0,3889 meter
*/
  int Aantal_Pos_Wielomwenteling = 1080;  // 30*36 (gearbox en positiewieltje)
  double Omtrek_Wiel = 0.3889;            // Formule omtrek
  double Omtrek_Op_Positie = 0.00036;     // 0.3889/1080

// Omzetten van snelheid (naar m/s)
// Inkomende waarde is = #posities/0.5sec
double Conv_Snelheid(int waarde)  {
  double Resultaat = waarde * 2;
  Resultaat = Omtrek_Op_Positie * Resultaat;
  return Resultaat;
}

// Omzetten van positie (naar m)
double Conv_Positie(int waarde)  {
  double Resultaat = Omtrek_Op_Positie * waarde;
  return Resultaat;
}
